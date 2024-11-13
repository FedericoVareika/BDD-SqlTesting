#!/bin/bash

sqlldr fede/hola123@xepdb1 control=load_asistentes.ctl log=~/load_files.log
sqlldr fede/hola123@xepdb1 control=load_roles.ctl log=~/load_files.log
sqlldr fede/hola123@xepdb1 control=load_asigna_roles.ctl log=~/load_files.log
sqlldr fede/hola123@xepdb1 control=load_configuraciones.ctl log=~/load_files.log
sqlldr fede/hola123@xepdb1 control=load_usuarios.ctl log=~/load_files.log
sqlldr fede/hola123@xepdb1 control=load_compras.ctl log=~/load_files.log
