#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FinalHSM2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FinalHSM2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=C:/CMPE118/src/AD.c C:/CMPE118/src/BOARD.c C:/CMPE118/src/ES_CheckEvents.c C:/CMPE118/src/ES_Framework.c C:/CMPE118/src/ES_KeyboardInput.c C:/CMPE118/src/ES_PostList.c C:/CMPE118/src/ES_Queue.c C:/CMPE118/src/ES_TattleTale.c C:/CMPE118/src/ES_Timers.c C:/CMPE118/src/IO_Ports.c C:/CMPE118/src/pwm.c C:/CMPE118/src/serial.c C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TemplateES_Main.c C:/Users/dchunter/MPLABXProjects/MyHelperFunctions.c C:/CMPE118/src/LED.c C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TapeTrackingSubHSM.c C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TopLevelHSM.c C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TrackWireSubHSM.c C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/FirstBeaconSubHSM.c C:/CMPE118/src/RC_Servo.c C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/EventChecker.c C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TemplateService.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/331920610/AD.o ${OBJECTDIR}/_ext/331920610/BOARD.o ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o ${OBJECTDIR}/_ext/331920610/ES_Framework.o ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o ${OBJECTDIR}/_ext/331920610/ES_PostList.o ${OBJECTDIR}/_ext/331920610/ES_Queue.o ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o ${OBJECTDIR}/_ext/331920610/ES_Timers.o ${OBJECTDIR}/_ext/331920610/IO_Ports.o ${OBJECTDIR}/_ext/331920610/pwm.o ${OBJECTDIR}/_ext/331920610/serial.o ${OBJECTDIR}/_ext/418869798/TemplateES_Main.o ${OBJECTDIR}/_ext/281976485/MyHelperFunctions.o ${OBJECTDIR}/_ext/331920610/LED.o ${OBJECTDIR}/_ext/418869798/TapeTrackingSubHSM.o ${OBJECTDIR}/_ext/418869798/TopLevelHSM.o ${OBJECTDIR}/_ext/418869798/TrackWireSubHSM.o ${OBJECTDIR}/_ext/418869798/FirstBeaconSubHSM.o ${OBJECTDIR}/_ext/331920610/RC_Servo.o ${OBJECTDIR}/_ext/418869798/EventChecker.o ${OBJECTDIR}/_ext/418869798/TemplateService.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/331920610/AD.o.d ${OBJECTDIR}/_ext/331920610/BOARD.o.d ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/331920610/ES_Framework.o.d ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/331920610/ES_PostList.o.d ${OBJECTDIR}/_ext/331920610/ES_Queue.o.d ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o.d ${OBJECTDIR}/_ext/331920610/ES_Timers.o.d ${OBJECTDIR}/_ext/331920610/IO_Ports.o.d ${OBJECTDIR}/_ext/331920610/pwm.o.d ${OBJECTDIR}/_ext/331920610/serial.o.d ${OBJECTDIR}/_ext/418869798/TemplateES_Main.o.d ${OBJECTDIR}/_ext/281976485/MyHelperFunctions.o.d ${OBJECTDIR}/_ext/331920610/LED.o.d ${OBJECTDIR}/_ext/418869798/TapeTrackingSubHSM.o.d ${OBJECTDIR}/_ext/418869798/TopLevelHSM.o.d ${OBJECTDIR}/_ext/418869798/TrackWireSubHSM.o.d ${OBJECTDIR}/_ext/418869798/FirstBeaconSubHSM.o.d ${OBJECTDIR}/_ext/331920610/RC_Servo.o.d ${OBJECTDIR}/_ext/418869798/EventChecker.o.d ${OBJECTDIR}/_ext/418869798/TemplateService.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/331920610/AD.o ${OBJECTDIR}/_ext/331920610/BOARD.o ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o ${OBJECTDIR}/_ext/331920610/ES_Framework.o ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o ${OBJECTDIR}/_ext/331920610/ES_PostList.o ${OBJECTDIR}/_ext/331920610/ES_Queue.o ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o ${OBJECTDIR}/_ext/331920610/ES_Timers.o ${OBJECTDIR}/_ext/331920610/IO_Ports.o ${OBJECTDIR}/_ext/331920610/pwm.o ${OBJECTDIR}/_ext/331920610/serial.o ${OBJECTDIR}/_ext/418869798/TemplateES_Main.o ${OBJECTDIR}/_ext/281976485/MyHelperFunctions.o ${OBJECTDIR}/_ext/331920610/LED.o ${OBJECTDIR}/_ext/418869798/TapeTrackingSubHSM.o ${OBJECTDIR}/_ext/418869798/TopLevelHSM.o ${OBJECTDIR}/_ext/418869798/TrackWireSubHSM.o ${OBJECTDIR}/_ext/418869798/FirstBeaconSubHSM.o ${OBJECTDIR}/_ext/331920610/RC_Servo.o ${OBJECTDIR}/_ext/418869798/EventChecker.o ${OBJECTDIR}/_ext/418869798/TemplateService.o

# Source Files
SOURCEFILES=C:/CMPE118/src/AD.c C:/CMPE118/src/BOARD.c C:/CMPE118/src/ES_CheckEvents.c C:/CMPE118/src/ES_Framework.c C:/CMPE118/src/ES_KeyboardInput.c C:/CMPE118/src/ES_PostList.c C:/CMPE118/src/ES_Queue.c C:/CMPE118/src/ES_TattleTale.c C:/CMPE118/src/ES_Timers.c C:/CMPE118/src/IO_Ports.c C:/CMPE118/src/pwm.c C:/CMPE118/src/serial.c C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TemplateES_Main.c C:/Users/dchunter/MPLABXProjects/MyHelperFunctions.c C:/CMPE118/src/LED.c C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TapeTrackingSubHSM.c C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TopLevelHSM.c C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TrackWireSubHSM.c C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/FirstBeaconSubHSM.c C:/CMPE118/src/RC_Servo.c C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/EventChecker.c C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TemplateService.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
Device=PIC32MX320F128H
ProjectDir="C:\Users\dchunter\MPLABXProjects\FinalHSM2.X"
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\FinalHSM2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="FinalHSM2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  .pre ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/FinalHSM2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=,--script="C:\CMPE118\bootloader320.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/331920610/AD.o: C:/CMPE118/src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/AD.o.d" -o ${OBJECTDIR}/_ext/331920610/AD.o C:/CMPE118/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/BOARD.o: C:/CMPE118/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/BOARD.o.d" -o ${OBJECTDIR}/_ext/331920610/BOARD.o C:/CMPE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o: C:/CMPE118/src/ES_CheckEvents.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o C:/CMPE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_Framework.o: C:/CMPE118/src/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_Framework.o C:/CMPE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o: C:/CMPE118/src/ES_KeyboardInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o C:/CMPE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_PostList.o: C:/CMPE118/src/ES_PostList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_PostList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_PostList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_PostList.o C:/CMPE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_Queue.o: C:/CMPE118/src/ES_Queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_Queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_Queue.o C:/CMPE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_TattleTale.o: C:/CMPE118/src/ES_TattleTale.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_TattleTale.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o C:/CMPE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_Timers.o: C:/CMPE118/src/ES_Timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_Timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_Timers.o C:/CMPE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/IO_Ports.o: C:/CMPE118/src/IO_Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/IO_Ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/IO_Ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/331920610/IO_Ports.o C:/CMPE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/pwm.o: C:/CMPE118/src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/pwm.o.d" -o ${OBJECTDIR}/_ext/331920610/pwm.o C:/CMPE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/serial.o: C:/CMPE118/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/serial.o.d" -o ${OBJECTDIR}/_ext/331920610/serial.o C:/CMPE118/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/418869798/TemplateES_Main.o: C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TemplateES_Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/418869798" 
	@${RM} ${OBJECTDIR}/_ext/418869798/TemplateES_Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/418869798/TemplateES_Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/418869798/TemplateES_Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/418869798/TemplateES_Main.o.d" -o ${OBJECTDIR}/_ext/418869798/TemplateES_Main.o C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TemplateES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/281976485/MyHelperFunctions.o: C:/Users/dchunter/MPLABXProjects/MyHelperFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/281976485" 
	@${RM} ${OBJECTDIR}/_ext/281976485/MyHelperFunctions.o.d 
	@${RM} ${OBJECTDIR}/_ext/281976485/MyHelperFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/281976485/MyHelperFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/281976485/MyHelperFunctions.o.d" -o ${OBJECTDIR}/_ext/281976485/MyHelperFunctions.o C:/Users/dchunter/MPLABXProjects/MyHelperFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/LED.o: C:/CMPE118/src/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/LED.o.d" -o ${OBJECTDIR}/_ext/331920610/LED.o C:/CMPE118/src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/418869798/TapeTrackingSubHSM.o: C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TapeTrackingSubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/418869798" 
	@${RM} ${OBJECTDIR}/_ext/418869798/TapeTrackingSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/418869798/TapeTrackingSubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/418869798/TapeTrackingSubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/418869798/TapeTrackingSubHSM.o.d" -o ${OBJECTDIR}/_ext/418869798/TapeTrackingSubHSM.o C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TapeTrackingSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/418869798/TopLevelHSM.o: C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TopLevelHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/418869798" 
	@${RM} ${OBJECTDIR}/_ext/418869798/TopLevelHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/418869798/TopLevelHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/418869798/TopLevelHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/418869798/TopLevelHSM.o.d" -o ${OBJECTDIR}/_ext/418869798/TopLevelHSM.o C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TopLevelHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/418869798/TrackWireSubHSM.o: C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TrackWireSubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/418869798" 
	@${RM} ${OBJECTDIR}/_ext/418869798/TrackWireSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/418869798/TrackWireSubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/418869798/TrackWireSubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/418869798/TrackWireSubHSM.o.d" -o ${OBJECTDIR}/_ext/418869798/TrackWireSubHSM.o C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TrackWireSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/418869798/FirstBeaconSubHSM.o: C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/FirstBeaconSubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/418869798" 
	@${RM} ${OBJECTDIR}/_ext/418869798/FirstBeaconSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/418869798/FirstBeaconSubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/418869798/FirstBeaconSubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/418869798/FirstBeaconSubHSM.o.d" -o ${OBJECTDIR}/_ext/418869798/FirstBeaconSubHSM.o C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/FirstBeaconSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/RC_Servo.o: C:/CMPE118/src/RC_Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/RC_Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/RC_Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/331920610/RC_Servo.o C:/CMPE118/src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/418869798/EventChecker.o: C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/EventChecker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/418869798" 
	@${RM} ${OBJECTDIR}/_ext/418869798/EventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/418869798/EventChecker.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/418869798/EventChecker.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/418869798/EventChecker.o.d" -o ${OBJECTDIR}/_ext/418869798/EventChecker.o C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/EventChecker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/418869798/TemplateService.o: C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TemplateService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/418869798" 
	@${RM} ${OBJECTDIR}/_ext/418869798/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/_ext/418869798/TemplateService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/418869798/TemplateService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/418869798/TemplateService.o.d" -o ${OBJECTDIR}/_ext/418869798/TemplateService.o C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TemplateService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/331920610/AD.o: C:/CMPE118/src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/AD.o.d" -o ${OBJECTDIR}/_ext/331920610/AD.o C:/CMPE118/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/BOARD.o: C:/CMPE118/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/BOARD.o.d" -o ${OBJECTDIR}/_ext/331920610/BOARD.o C:/CMPE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o: C:/CMPE118/src/ES_CheckEvents.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o C:/CMPE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_Framework.o: C:/CMPE118/src/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_Framework.o C:/CMPE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o: C:/CMPE118/src/ES_KeyboardInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o C:/CMPE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_PostList.o: C:/CMPE118/src/ES_PostList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_PostList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_PostList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_PostList.o C:/CMPE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_Queue.o: C:/CMPE118/src/ES_Queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_Queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_Queue.o C:/CMPE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_TattleTale.o: C:/CMPE118/src/ES_TattleTale.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_TattleTale.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o C:/CMPE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_Timers.o: C:/CMPE118/src/ES_Timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_Timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_Timers.o C:/CMPE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/IO_Ports.o: C:/CMPE118/src/IO_Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/IO_Ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/IO_Ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/331920610/IO_Ports.o C:/CMPE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/pwm.o: C:/CMPE118/src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/pwm.o.d" -o ${OBJECTDIR}/_ext/331920610/pwm.o C:/CMPE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/serial.o: C:/CMPE118/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/serial.o.d" -o ${OBJECTDIR}/_ext/331920610/serial.o C:/CMPE118/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/418869798/TemplateES_Main.o: C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TemplateES_Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/418869798" 
	@${RM} ${OBJECTDIR}/_ext/418869798/TemplateES_Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/418869798/TemplateES_Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/418869798/TemplateES_Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/418869798/TemplateES_Main.o.d" -o ${OBJECTDIR}/_ext/418869798/TemplateES_Main.o C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TemplateES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/281976485/MyHelperFunctions.o: C:/Users/dchunter/MPLABXProjects/MyHelperFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/281976485" 
	@${RM} ${OBJECTDIR}/_ext/281976485/MyHelperFunctions.o.d 
	@${RM} ${OBJECTDIR}/_ext/281976485/MyHelperFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/281976485/MyHelperFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/281976485/MyHelperFunctions.o.d" -o ${OBJECTDIR}/_ext/281976485/MyHelperFunctions.o C:/Users/dchunter/MPLABXProjects/MyHelperFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/LED.o: C:/CMPE118/src/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/LED.o.d" -o ${OBJECTDIR}/_ext/331920610/LED.o C:/CMPE118/src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/418869798/TapeTrackingSubHSM.o: C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TapeTrackingSubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/418869798" 
	@${RM} ${OBJECTDIR}/_ext/418869798/TapeTrackingSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/418869798/TapeTrackingSubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/418869798/TapeTrackingSubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/418869798/TapeTrackingSubHSM.o.d" -o ${OBJECTDIR}/_ext/418869798/TapeTrackingSubHSM.o C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TapeTrackingSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/418869798/TopLevelHSM.o: C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TopLevelHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/418869798" 
	@${RM} ${OBJECTDIR}/_ext/418869798/TopLevelHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/418869798/TopLevelHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/418869798/TopLevelHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/418869798/TopLevelHSM.o.d" -o ${OBJECTDIR}/_ext/418869798/TopLevelHSM.o C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TopLevelHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/418869798/TrackWireSubHSM.o: C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TrackWireSubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/418869798" 
	@${RM} ${OBJECTDIR}/_ext/418869798/TrackWireSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/418869798/TrackWireSubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/418869798/TrackWireSubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/418869798/TrackWireSubHSM.o.d" -o ${OBJECTDIR}/_ext/418869798/TrackWireSubHSM.o C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TrackWireSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/418869798/FirstBeaconSubHSM.o: C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/FirstBeaconSubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/418869798" 
	@${RM} ${OBJECTDIR}/_ext/418869798/FirstBeaconSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/418869798/FirstBeaconSubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/418869798/FirstBeaconSubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/418869798/FirstBeaconSubHSM.o.d" -o ${OBJECTDIR}/_ext/418869798/FirstBeaconSubHSM.o C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/FirstBeaconSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/RC_Servo.o: C:/CMPE118/src/RC_Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/RC_Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/RC_Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/331920610/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/331920610/RC_Servo.o C:/CMPE118/src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/418869798/EventChecker.o: C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/EventChecker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/418869798" 
	@${RM} ${OBJECTDIR}/_ext/418869798/EventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/418869798/EventChecker.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/418869798/EventChecker.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/418869798/EventChecker.o.d" -o ${OBJECTDIR}/_ext/418869798/EventChecker.o C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/EventChecker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/418869798/TemplateService.o: C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TemplateService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/418869798" 
	@${RM} ${OBJECTDIR}/_ext/418869798/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/_ext/418869798/TemplateService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/418869798/TemplateService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/Users/dchunter/MPLABXProjects" -I"C:/Users/dchunter/MPLABXProjects/FinalHSM2.X" -MMD -MF "${OBJECTDIR}/_ext/418869798/TemplateService.o.d" -o ${OBJECTDIR}/_ext/418869798/TemplateService.o C:/Users/dchunter/MPLABXProjects/FinalHSM2.X/TemplateService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/FinalHSM2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    C:/CMPE118/bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/FinalHSM2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)    -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=10,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/FinalHSM2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   C:/CMPE118/bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/FinalHSM2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=10,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/FinalHSM2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif

.pre:
	@echo "--------------------------------------"
	@echo "User defined pre-build step: [python C:\CMPE118\scripts\Enum_To_String.py]"
	@python C:\CMPE118\scripts\Enum_To_String.py
	@echo "--------------------------------------"

# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
