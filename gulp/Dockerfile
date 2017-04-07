FROM node:argon
# we use this old version, because otherwise we get obscure errors when we do `npm install` in a vmware shared folder, probably because of parallelization of later versions, just a guess 
# https://github.com/npm/npm/issues/15034


RUN npm install --global gulp-cli

# they already added the user
USER node

RUN mkdir ~/prj
WORKDIR /home/node/prj
COPY package.json .
COPY gulpfile.js .

RUN npm install

CMD gulp

