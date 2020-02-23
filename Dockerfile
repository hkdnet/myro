FROM node:12.16.1

RUN mkdir -p /app

WORKDIR /app

COPY package.json package-lock.json /app/
RUN npm i

COPY . /app
RUN npm run build

CMD ["node", "main.js"]
