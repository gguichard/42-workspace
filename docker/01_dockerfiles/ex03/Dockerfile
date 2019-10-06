FROM ruby

WORKDIR /root

RUN curl -sS https://dl.yarnpkg.com/debian/pubkey.gpg | apt-key add - \
	&& echo "deb https://dl.yarnpkg.com/debian/ stable main" | tee /etc/apt/sources.list.d/yarn.list

RUN apt-get update \
	&& apt-get upgrade -y \
	&& apt-get install -y build-essential zlib1g-dev libyaml-dev libssl-dev libgdbm-dev libre2-dev \
		libreadline-dev libncurses5-dev libffi-dev curl openssh-server checkinstall libxml2-dev \
		libxslt-dev libcurl4-openssl-dev libicu-dev logrotate rsync python-docutils pkg-config cmake \
		runit git-core postgresql postgresql-client libpq-dev postgresql-contrib nginx nodejs yarn redis-server \
	&& curl --remote-name --progress https://dl.google.com/go/go1.11.10.linux-amd64.tar.gz \
	&& tar -C /usr/local -xzf go1.11.10.linux-amd64.tar.gz \
	&& ln -sf /usr/local/go/bin/{go,godoc,gofmt} /usr/local/bin/ \
	&& go1.11.10.linux-amd64.tar.gz \
	&& adduser --disabled-login --gecos 'GitLab' git

USER postgres

RUN psql -d template1 -c "CREATE USER git CREATEDB;" \
	&& psql -d template1 -c "CREATE EXTENSION IF NOT EXISTS pg_trgm;" \
	&& psql -d template1 -c "CREATE DATABASE gitlabhq_production OWNER git;" \

USER git
WORKDIR /home/git

RUN git clone https://gitlab.com/gitlab-org/gitlab-shell.git

WORKDIR gitlab-shell

RUN cat config.yml.example | tr "localhost" "0.0.0.0" > config.yml \
	&& ./bin/install

WORKDIR /home/git

RUN git clone https://gitlab.com/gitlab-org/gitlab-foss.git

WORKDIR gitlab

RUN chown -R git log \
	&& chown -R git log \
	&& chown -R git tmp \
	&& chmod -R u+rwX,go-w log \
	&& chmod -R u+rwX tmp \
	&& chmod -R u+rwX tmp/pids \
	&& chmod -R u+rwX tmp/sockets \
	&& mkdir -p public/uploads \
	&& chmod 0700 public/uploads \
	&& chmod -R u+rwX builds \
	&& chmod -R u+rwX shared/artifacts \
	&& chmod -R ug+rwX shared/pages \
	&& cp config/gitlab.yml.example config/gitlab.yml \
	&& cp config/unicorn.rb.example config/unicorn.rb \
	&& cp config/database.yml.env config/database.yml \
	&& cp config/initializers/rack_attack.rb.example config/initializers/rack_attack.rb \
	&& cp config/resque.yml.example config/resque.yml \
	&& bundle install --deployment --without development test mysql aws kerberos \
	&& bundle exec rake gitlab:env:info RAILS_ENV=production

USER root

RUN cp lib/support/logrotate/gitlab /etc/logrotate.d/gitlab \
	&& cp lib/support/nginx/gitlab /etc/nginx/sites-available/gitlab \
	&& ln -s /etc/nginx/sites-available/gitlab /etc/nginx/sites-enabled/gitlab \
	&& service nginx restart

ENTRYPOINT ["service gitlab start"]
