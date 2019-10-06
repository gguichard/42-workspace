FROM debian

EXPOSE 30033/tcp
EXPOSE 9987/udp
EXPOSE 10011/tcp

WORKDIR /root

RUN apt-get update \
	&& apt-get upgrade -y \
	&& apt-get install -y wget bzip2 \
	&& useradd --create-home teamspeak

USER teamspeak
WORKDIR /home/teamspeak

RUN wget https://files.teamspeak-services.com/releases/server/3.9.1/teamspeak3-server_linux_amd64-3.9.1.tar.bz2 \
	&& bzip2 -dc teamspeak3-server_linux_amd64-3.9.1.tar.bz2 | tar -xf -

WORKDIR teamspeak3-server_linux_amd64

ENV TS3SERVER_LICENSE=accept
RUN chmod +x ts3server_minimal_runscript.sh

ENTRYPOINT ["./ts3server_minimal_runscript.sh", "tail -f /dev/null"]
