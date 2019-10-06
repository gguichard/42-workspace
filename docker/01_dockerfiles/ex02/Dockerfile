FROM ruby

EXPOSE 3000/tcp

RUN curl -sS https://dl.yarnpkg.com/debian/pubkey.gpg | apt-key add - \
	&& echo "deb https://dl.yarnpkg.com/debian/ stable main" | tee /etc/apt/sources.list.d/yarn.list \
	&& apt-get update \
	&& apt-get upgrade -y \
	&& apt-get install -y nodejs yarn \
	&& gem install rails faker populator

WORKDIR /opt/app

COPY rails .

RUN rails db:migrate \
	&& rails db:seed

ENTRYPOINT ["rails server"]
CMD ["-b 0.0.0.0", "-p 3000"]
