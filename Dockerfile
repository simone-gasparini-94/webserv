FROM ubuntu:24.04

RUN apt-get update && apt-get install -y build-essential

WORKDIR /app

COPY . .

RUN make

ENTRYPOINT ["./webserv"]

CMD ["conf-files/webserv.conf"]
