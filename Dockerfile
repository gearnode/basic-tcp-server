FROM alpine:3.8 as builder

WORKDIR /tmp/basic-tcp-server

RUN apk add --no-cache make gcc libc-dev

COPY . .

RUN make

FROM alpine:3.8

COPY --from=builder /tmp/basic-tcp-server/bin/server /bin/basic-tcp-server

CMD ["basic-tcp-server"]
