FROM ruby

ENV RAILS_ENV=production
ENV GITLAB_DATABASE_HOST=''

WORKDIR /root

# Setup yarn source
RUN curl -sS https://dl.yarnpkg.com/debian/pubkey.gpg | apt-key add - \
	&& echo "deb https://dl.yarnpkg.com/debian/ stable main" | tee /etc/apt/sources.list.d/yarn.list

# Update & install needed packages
RUN apt-get update \
	&& apt-get upgrade -y \
	&& apt-get install -y sudo \
	&& apt-get install -y build-essential zlib1g-dev libyaml-dev libssl-dev libgdbm-dev libre2-dev \
		libreadline-dev libncurses5-dev libffi-dev curl openssh-server libxml2-dev \
		libxslt-dev libcurl4-openssl-dev libicu-dev logrotate rsync python-docutils pkg-config cmake \
		git-core postgresql postgresql-client libpq-dev postgresql-contrib nginx nodejs yarn redis-server

# Install Go
RUN curl --remote-name --progress https://dl.google.com/go/go1.11.10.linux-amd64.tar.gz \
	&& tar -C /usr/local -xzf go1.11.10.linux-amd64.tar.gz \
	&& ln -sf /usr/local/go/bin/go /usr/local/bin/ \
	&& ln -sf /usr/local/go/bin/godoc /usr/local/bin/ \
	&& ln -sf /usr/local/go/bin/gofmt /usr/local/bin/ \
	&& rm go1.11.10.linux-amd64.tar.gz

# Create git user for gitlab
RUN adduser --disabled-login --gecos 'GitLab' git

# Setup postgres database
USER postgres
WORKDIR /home/postgres

RUN pg_ctlcluster 11 main start \
	&& psql -d template1 -c "CREATE USER git CREATEDB;" \
	&& psql -d template1 -c "CREATE EXTENSION IF NOT EXISTS pg_trgm;" \
	&& psql -d template1 -c "CREATE DATABASE gitlab_production OWNER git;"

# Clone gitlab-foss
USER git
WORKDIR /home/git

RUN git clone https://gitlab.com/gitlab-org/gitlab-foss.git gitlab

# Setup right permissions
USER root
WORKDIR /home/git/gitlab

RUN chown -R git log \
	&& chown -R git log \
	&& chown -R git tmp \
	&& chmod -R u+rwX,go-w log \
	&& chmod -R u+rwX tmp \
	&& chmod -R u+rwX tmp/pids \
	&& chmod -R u+rwX tmp/sockets \
	&& chmod -R u+rwX builds \
	&& chmod -R u+rwX shared/artifacts \
	&& chmod -R ug+rwX shared/pages

# Copy configs
USER git

RUN mkdir -p public/uploads \
	&& chmod 0700 public/uploads \
	&& cp config/gitlab.yml.example config/gitlab.yml \
	&& cp config/unicorn.rb.example config/unicorn.rb \
	&& cp config/database.yml.env config/database.yml \
	&& cp config/initializers/rack_attack.rb.example config/initializers/rack_attack.rb \
	&& cp config/resque.yml.example config/resque.yml

# Install gems
RUN bundle install --deployment --without development test mysql aws kerberos

RUN bundle exec rake gitlab:shell:install REDIS_URL=unix:/var/run/redis/redis.sock SKIP_STORAGE_VALIDATION=true \
	&& bundle exec rake "gitlab:workhorse:install[/home/git/gitlab-workhorse]" \
	&& bundle exec rake "gitlab:gitaly:install[/home/git/gitaly,/home/git/repositories]"

# Run gitaly
RUN /home/git/gitlab/bin/daemon_with_pidfile /home/git/gitlab/tmp/pids/gitaly.pid /home/git/gitaly/gitaly /home/git/gitaly/config.toml >> /home/git/gitlab/log/gitaly.log 2>&1 &

# Setup gitlab
RUN bundle exec rake gitlab:setup force=yes \
	&& bundle exec rake gettext:compile \
	&& yarn install --production --pure-lockfile \
	&& bundle exec rake gitlab:assets:compile NODE_ENV=production

# Run gitlab
USER root

RUN cp lib/support/init.d/gitlab /etc/init.d/gitlab \
	&& cp lib/support/init.d/gitlab.default.example /etc/default/gitlab \
	&& update-rc.d gitlab defaults 21 \
	&& service gitlab start \
	&& cp lib/support/logrotate/gitlab /etc/logrotate.d/gitlab \
	&& cp lib/support/nginx/gitlab /etc/nginx/sites-available/gitlab \
	&& ln -s /etc/nginx/sites-available/gitlab /etc/nginx/sites-enabled/gitlab \
	&& rm /etc/nginx/sites-enabled/default \
	&& service nginx restart

ENTRYPOINT ["service gitlab start"]
