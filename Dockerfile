FROM arm64v8/alpine:3.20

WORKDIR /casper/dev/

COPY . /casper/dev/

RUN apk update && apk add build-base

CMD ["sh", "-c", "as --version && ld --version"]
