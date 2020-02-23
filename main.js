require('isomorphic-fetch');

const Server = require('./src/Server.bs.js');

let server = Server.start(process.env.NATURE_TOKEN, process.env.PORT || 3000);
process.on('SIGTERM', () => {
    server.close(() => {
        console.log('Process terminated.')
    })
});
