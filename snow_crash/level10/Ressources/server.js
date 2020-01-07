require('net').createServer(function (socket) {
    console.log('new client')

    socket.on('data', function (data) {
        console.log(data.toString())
    })
}).listen(6969)
