#!/bin/bash

session=fede/hola123@xepdb1
log=~/load_files.log

dir=${BASH_SOURCE%/*}
sql_scripts=${dir%/*}

sqlplus $session @$sql_scripts/ddl.sql

cd -- $dir
sqlldr $session control=load_asistentes.ctl         log=$log
sqlldr $session control=load_roles.ctl              log=$log
sqlldr $session control=load_asigna_roles.ctl       log=$log
sqlldr $session control=load_configuraciones.ctl    log=$log
sqlldr $session control=load_usuarios.ctl           log=$log
sqlldr $session control=load_compras.ctl            log=$log
