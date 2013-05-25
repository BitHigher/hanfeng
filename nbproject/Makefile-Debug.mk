#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/base/init.o \
	${OBJECTDIR}/base/memory.o \
	${OBJECTDIR}/io/HFIO.o \
	${OBJECTDIR}/lib/HFException.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/math/Math.o \
	${OBJECTDIR}/structure/HFMatrix.o \
	${OBJECTDIR}/structure/HFReferenceData.o \
	${OBJECTDIR}/structure/HFVector.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hanfeng

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hanfeng: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hanfeng ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/base/init.o: base/init.cpp 
	${MKDIR} -p ${OBJECTDIR}/base
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/base/init.o base/init.cpp

${OBJECTDIR}/base/memory.o: base/memory.cpp 
	${MKDIR} -p ${OBJECTDIR}/base
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/base/memory.o base/memory.cpp

${OBJECTDIR}/io/HFIO.o: io/HFIO.cpp 
	${MKDIR} -p ${OBJECTDIR}/io
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/io/HFIO.o io/HFIO.cpp

${OBJECTDIR}/lib/HFException.o: lib/HFException.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/HFException.o lib/HFException.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/math/Math.o: math/Math.cpp 
	${MKDIR} -p ${OBJECTDIR}/math
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/math/Math.o math/Math.cpp

${OBJECTDIR}/structure/HFMatrix.o: structure/HFMatrix.cpp 
	${MKDIR} -p ${OBJECTDIR}/structure
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/structure/HFMatrix.o structure/HFMatrix.cpp

${OBJECTDIR}/structure/HFReferenceData.o: structure/HFReferenceData.cpp 
	${MKDIR} -p ${OBJECTDIR}/structure
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/structure/HFReferenceData.o structure/HFReferenceData.cpp

${OBJECTDIR}/structure/HFVector.o: structure/HFVector.cpp 
	${MKDIR} -p ${OBJECTDIR}/structure
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/structure/HFVector.o structure/HFVector.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hanfeng

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
