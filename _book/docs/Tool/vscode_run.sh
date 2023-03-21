#!/bin/sh
PATH=`pwd $0`
HOST={ip_address}
PORT={port}

export PASSWORD="password"

cd ${PATH}/vscode-server/

pwd
exec "code-server --port ${PORT} --host ${HOST}"
