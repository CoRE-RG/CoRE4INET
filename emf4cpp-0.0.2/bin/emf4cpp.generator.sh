#! /bin/sh
#
# emf4cpp.generator.sh
# Copyright (C) Cátedra SAES-UMU 2010 <andres.senac@um.es>
# 
# EMF4CPP is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# EMF4CPP is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# 

BASEDIR=$(dirname $0)
GENERATOR_DIR=${BASEDIR}

# Default options
DEST_DIR="."
ECORECPP_PATH="${GENERATOR_DIR}/../include/emf4cpp"


# Go go go
JAR="${BASEDIR}/org.csu.emf4cpp.generator_1.0.0.jar"
java -jar ${JAR} -e ${ECORECPP_PATH} -o ${DEST_DIR} $@
