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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/base/DataType.o \
	${OBJECTDIR}/base/HFObject.o \
	${OBJECTDIR}/base/Parallel.o \
	${OBJECTDIR}/base/Parameter.o \
	${OBJECTDIR}/base/ParameterMap.o \
	${OBJECTDIR}/base/Version.o \
	${OBJECTDIR}/base/init.o \
	${OBJECTDIR}/base/memory.o \
	${OBJECTDIR}/classifier/LDA.o \
	${OBJECTDIR}/classifier/LPM.o \
	${OBJECTDIR}/classifier/Perceptron.o \
	${OBJECTDIR}/clustering/KMeans.o \
	${OBJECTDIR}/distance/Distance.o \
	${OBJECTDIR}/features/DenseFeatures.o \
	${OBJECTDIR}/features/DotFeatures.o \
	${OBJECTDIR}/features/Features.o \
	${OBJECTDIR}/io/File.o \
	${OBJECTDIR}/io/HFIO.o \
	${OBJECTDIR}/labels/BinaryLabels.o \
	${OBJECTDIR}/labels/DenseLabels.o \
	${OBJECTDIR}/labels/Labels.o \
	${OBJECTDIR}/labels/LatentLabels.o \
	${OBJECTDIR}/labels/MultiClassLabels.o \
	${OBJECTDIR}/labels/RegressionLabels.o \
	${OBJECTDIR}/labels/StructuredLabels.o \
	${OBJECTDIR}/lib/HFException.o \
	${OBJECTDIR}/loss/LogLoss.o \
	${OBJECTDIR}/machine/DistanceMachine.o \
	${OBJECTDIR}/machine/LinearMachine.o \
	${OBJECTDIR}/machine/Machine.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/math/Math.o \
	${OBJECTDIR}/math/lapack.o \
	${OBJECTDIR}/multiclass/KNN.o \
	${OBJECTDIR}/regression/LeastSquaresRegression.o \
	${OBJECTDIR}/regression/LinearRidgeRegression.o \
	${OBJECTDIR}/structure/HFMatrix.o \
	${OBJECTDIR}/structure/HFReferenceData.o \
	${OBJECTDIR}/structure/HFVector.o \
	${OBJECTDIR}/structure/Subset.o \
	${OBJECTDIR}/structure/SubsetStack.o


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

${OBJECTDIR}/base/DataType.o: base/DataType.cpp 
	${MKDIR} -p ${OBJECTDIR}/base
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/base/DataType.o base/DataType.cpp

${OBJECTDIR}/base/HFObject.o: base/HFObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/base
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/base/HFObject.o base/HFObject.cpp

${OBJECTDIR}/base/Parallel.o: base/Parallel.cpp 
	${MKDIR} -p ${OBJECTDIR}/base
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/base/Parallel.o base/Parallel.cpp

${OBJECTDIR}/base/Parameter.o: base/Parameter.cpp 
	${MKDIR} -p ${OBJECTDIR}/base
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/base/Parameter.o base/Parameter.cpp

${OBJECTDIR}/base/ParameterMap.o: base/ParameterMap.cpp 
	${MKDIR} -p ${OBJECTDIR}/base
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/base/ParameterMap.o base/ParameterMap.cpp

${OBJECTDIR}/base/Version.o: base/Version.cpp 
	${MKDIR} -p ${OBJECTDIR}/base
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/base/Version.o base/Version.cpp

${OBJECTDIR}/base/init.o: base/init.cpp 
	${MKDIR} -p ${OBJECTDIR}/base
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/base/init.o base/init.cpp

${OBJECTDIR}/base/memory.o: base/memory.cpp 
	${MKDIR} -p ${OBJECTDIR}/base
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/base/memory.o base/memory.cpp

${OBJECTDIR}/classifier/LDA.o: classifier/LDA.cpp 
	${MKDIR} -p ${OBJECTDIR}/classifier
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/classifier/LDA.o classifier/LDA.cpp

${OBJECTDIR}/classifier/LPM.o: classifier/LPM.cpp 
	${MKDIR} -p ${OBJECTDIR}/classifier
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/classifier/LPM.o classifier/LPM.cpp

${OBJECTDIR}/classifier/Perceptron.o: classifier/Perceptron.cpp 
	${MKDIR} -p ${OBJECTDIR}/classifier
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/classifier/Perceptron.o classifier/Perceptron.cpp

${OBJECTDIR}/clustering/KMeans.o: clustering/KMeans.cpp 
	${MKDIR} -p ${OBJECTDIR}/clustering
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/clustering/KMeans.o clustering/KMeans.cpp

${OBJECTDIR}/distance/Distance.o: distance/Distance.cpp 
	${MKDIR} -p ${OBJECTDIR}/distance
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/distance/Distance.o distance/Distance.cpp

${OBJECTDIR}/features/DenseFeatures.o: features/DenseFeatures.cpp 
	${MKDIR} -p ${OBJECTDIR}/features
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/features/DenseFeatures.o features/DenseFeatures.cpp

${OBJECTDIR}/features/DotFeatures.o: features/DotFeatures.cpp 
	${MKDIR} -p ${OBJECTDIR}/features
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/features/DotFeatures.o features/DotFeatures.cpp

${OBJECTDIR}/features/Features.o: features/Features.cpp 
	${MKDIR} -p ${OBJECTDIR}/features
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/features/Features.o features/Features.cpp

${OBJECTDIR}/io/File.o: io/File.cpp 
	${MKDIR} -p ${OBJECTDIR}/io
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/io/File.o io/File.cpp

${OBJECTDIR}/io/HFIO.o: io/HFIO.cpp 
	${MKDIR} -p ${OBJECTDIR}/io
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/io/HFIO.o io/HFIO.cpp

${OBJECTDIR}/labels/BinaryLabels.o: labels/BinaryLabels.cpp 
	${MKDIR} -p ${OBJECTDIR}/labels
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/labels/BinaryLabels.o labels/BinaryLabels.cpp

${OBJECTDIR}/labels/DenseLabels.o: labels/DenseLabels.cpp 
	${MKDIR} -p ${OBJECTDIR}/labels
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/labels/DenseLabels.o labels/DenseLabels.cpp

${OBJECTDIR}/labels/Labels.o: labels/Labels.cpp 
	${MKDIR} -p ${OBJECTDIR}/labels
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/labels/Labels.o labels/Labels.cpp

${OBJECTDIR}/labels/LatentLabels.o: labels/LatentLabels.cpp 
	${MKDIR} -p ${OBJECTDIR}/labels
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/labels/LatentLabels.o labels/LatentLabels.cpp

${OBJECTDIR}/labels/MultiClassLabels.o: labels/MultiClassLabels.cpp 
	${MKDIR} -p ${OBJECTDIR}/labels
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/labels/MultiClassLabels.o labels/MultiClassLabels.cpp

${OBJECTDIR}/labels/RegressionLabels.o: labels/RegressionLabels.cpp 
	${MKDIR} -p ${OBJECTDIR}/labels
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/labels/RegressionLabels.o labels/RegressionLabels.cpp

${OBJECTDIR}/labels/StructuredLabels.o: labels/StructuredLabels.cpp 
	${MKDIR} -p ${OBJECTDIR}/labels
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/labels/StructuredLabels.o labels/StructuredLabels.cpp

${OBJECTDIR}/lib/HFException.o: lib/HFException.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/HFException.o lib/HFException.cpp

${OBJECTDIR}/loss/LogLoss.o: loss/LogLoss.cpp 
	${MKDIR} -p ${OBJECTDIR}/loss
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/loss/LogLoss.o loss/LogLoss.cpp

${OBJECTDIR}/machine/DistanceMachine.o: machine/DistanceMachine.cpp 
	${MKDIR} -p ${OBJECTDIR}/machine
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/machine/DistanceMachine.o machine/DistanceMachine.cpp

${OBJECTDIR}/machine/LinearMachine.o: machine/LinearMachine.cpp 
	${MKDIR} -p ${OBJECTDIR}/machine
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/machine/LinearMachine.o machine/LinearMachine.cpp

${OBJECTDIR}/machine/Machine.o: machine/Machine.cpp 
	${MKDIR} -p ${OBJECTDIR}/machine
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/machine/Machine.o machine/Machine.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/math/Math.o: math/Math.cpp 
	${MKDIR} -p ${OBJECTDIR}/math
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/math/Math.o math/Math.cpp

${OBJECTDIR}/math/lapack.o: math/lapack.cpp 
	${MKDIR} -p ${OBJECTDIR}/math
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/math/lapack.o math/lapack.cpp

${OBJECTDIR}/multiclass/KNN.o: multiclass/KNN.cpp 
	${MKDIR} -p ${OBJECTDIR}/multiclass
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/multiclass/KNN.o multiclass/KNN.cpp

${OBJECTDIR}/regression/LeastSquaresRegression.o: regression/LeastSquaresRegression.cpp 
	${MKDIR} -p ${OBJECTDIR}/regression
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/regression/LeastSquaresRegression.o regression/LeastSquaresRegression.cpp

${OBJECTDIR}/regression/LinearRidgeRegression.o: regression/LinearRidgeRegression.cpp 
	${MKDIR} -p ${OBJECTDIR}/regression
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/regression/LinearRidgeRegression.o regression/LinearRidgeRegression.cpp

${OBJECTDIR}/structure/HFMatrix.o: structure/HFMatrix.cpp 
	${MKDIR} -p ${OBJECTDIR}/structure
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/structure/HFMatrix.o structure/HFMatrix.cpp

${OBJECTDIR}/structure/HFReferenceData.o: structure/HFReferenceData.cpp 
	${MKDIR} -p ${OBJECTDIR}/structure
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/structure/HFReferenceData.o structure/HFReferenceData.cpp

${OBJECTDIR}/structure/HFVector.o: structure/HFVector.cpp 
	${MKDIR} -p ${OBJECTDIR}/structure
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/structure/HFVector.o structure/HFVector.cpp

${OBJECTDIR}/structure/Subset.o: structure/Subset.cpp 
	${MKDIR} -p ${OBJECTDIR}/structure
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/structure/Subset.o structure/Subset.cpp

${OBJECTDIR}/structure/SubsetStack.o: structure/SubsetStack.cpp 
	${MKDIR} -p ${OBJECTDIR}/structure
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/structure/SubsetStack.o structure/SubsetStack.cpp

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
