require('isomorphic-fetch');

const Server = require('./src/Server.bs.js');

let server = Server.start(process.env.NATURE_TOKEN, process.env.PORT || 3000);
let h = () => {
    server.close(() => {
        console.log('Process terminated.')
    });
};
process.on('SIGTERM', h);
process.on('SIGINT', h);
