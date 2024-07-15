#!/bin/sh

###############################################################################
###############################################################################
# FUNCTIONS

function die ()
{
   printf '%s\n' "$1" >&2
   exit 1
}

function print_debug ()
{
   if [ ! -z "${OPT_VERBOSE}" ] && [ "${OPT_VERBOSE}" -ge "$1" ]; then
      printf '%s\n' "$2" >&2
   fi
}

function CHECK_FILEOBJ ()
{
   if [ "$1" = "DIR" ]; then
      if [ ! -d "$3" ] || [ ! -r "$3" ]; then
         die "ERROR: $2 not a directory or unreadable at \`$3\'. Bye."
      fi
   elif [ "$1" = "EXE" ]; then
      if [ ! -x "$3" ]; then
         die "ERROR: $2 not executable or present at \`$3\'. Bye."
         exit 1
      fi
   elif [ "$1" = "RW" ]; then
      if [ ! -w "$3" ] || [ ! -r "$3" ]; then
         die "ERROR: $2 not readable or writeable at \`$3\'. Bye."
         exit 1
      fi
   elif [ "$1" = "RO" ]; then
      if [ ! -w "$3" ] || [ ! -r "$3" ]; then
         die "ERROR: $2 not readable at \`$3\'. Bye."
         exit 1
      fi
   elif [ "$1" = "STR" ]; then
      if [ -z "$3" ]; then
         die "ERROR: \$$2 empty or undefied. Bye."
      fi
   else
      echo Function DEFINE_FILEOBJ called with illegal argument \`$1\'. Bye.
      exit 1
   fi
}

function DEFINE_FILEOBJ ()
{
   CHECK_FILEOBJ $1 $2 $3

   export $2=$3
   print_debug 2 "$2=$3"
}

function CHECK_RESULT ()
{
   local status=$?
   if [ $status -ne 0 ]; then
      printf "\`$1\' returned error code $status. Bye."
      exit $status
   fi
}

function CHECK_RESULT_2 ()
{
   local status=$?
   if [ "$status" -ge "2" ]; then
      printf "\`$1\' returned error code $status. Bye."
      exit $status
   fi
}

function show_help ()
{
	printf "Usage: ${SCRIPT_NAME} -e env_data -r VxxRxx [--no-sources|--no-lint|--no-doxygen|--no-latex|--no-doc-copy]\n"
	printf "Usage: ${SCRIPT_NAME} -h|--help\n"
   printf "\t-e|--env-data <env_data>\n"
   printf "\t--envdata=<env_data>         Environḿent data to import\n"
   printf "\t-r|--release-version VxxRxx\n"
   printf "\t--release-version=VxxRxx     Release version number\n"
   printf "\t--no-sources                 Do not generate source files\n"
   printf "\t--no-c-sources               Do not generate c source files\n"
   printf "\t--no-h-sources               Do not generate h source files\n"
   printf "\t--no-doxy-sources            Do not collect doxy source files\n"
   printf "\t--no-lint                    Do not create lint report\n"
   printf "\t--no-doxygen                 Do not generate doxygen\n"
   printf "\t--no-latex                   Do not create latex from doxygen\n"
   printf "\t--no-doc-copy                Do not copy documentation\n"
   printf "\n"
   printf "\t-h|--help                    Print help\n"
   printf "\n"
}

###############################################################################
###############################################################################
# Input parameter check

SCRIPT_NAME=`basename $0`
SCRIPT_PATH=`dirname $0`

# Initialize all the option variables.
# This ensures we are not contaminated by variables from the environment.
file=
verbose=0

while :; do
   case $1 in
      -h|-\?|--help)
         show_help    # Display a usage synopsis.
         exit
         ;;
      -r|--release-version)
         if [ "$2" ]; then
            RELEASE_VERSION=$2
            shift
         else
            die 'ERROR: "--release-version" requires a non-empty option argument.'
         fi
         ;;
      --release-version=?*)
         RELEASE_VERSION=${1#*=} # Delete everything up to "=" and assign the remainder.
         ;;
      --release-version=)         # Handle the case of an empty --file=
         die 'ERROR: "--release-version" requires a non-empty option argument.'
         ;;
      -e|--env)       # Takes an option argument; ensure it has been specified.
         if [ "$2" ]; then
            ENV_DATA=$2
            shift
         else
            die 'ERROR: "--env" requires a non-empty option argument.'
         fi
         ;;
      --env=?*)
         ENV_DATA=${1#*=} # Delete everything up to "=" and assign the remainder.
         ;;
      --env=)         # Handle the case of an empty --file=
         die 'ERROR: "--env" requires a non-empty option argument.'
         ;;
      --no-sources)
         OPT_NO_SOURCES=1
         ;;
      --no-c-sources)
         OPT_NO_C_SOURCES=1
         ;;
      --no-h-sources)
         OPT_NO_H_SOURCES=1
         ;;
      --no-doxy-sources)
         OPT_NO_DOXY_SOURCES=1
         ;;
      --no-lint)
         OPT_NO_LINT=1
         ;;
      --no-doxygen)
         OPT_NO_DOXYGEN=1
         ;;
      --no-latex)
         OPT_NO_LATEX=1
         ;;
      --no-doc-copy)
         OPT_NO_DOC_COPY=1
         ;;
      -v|--verbose)
         OPT_VERBOSE=$((OPT_VERBOSE + 1))  # Each -v adds 1 to verbosity.
         COPY_OPT="-v"
         ;;
      --)              # End of all options.
         shift
         break
         ;;
      -?*)
         printf 'ERROR: Unknown option: %s\n' "$1" >&2
         exit 1
         ;;
      *)               # Default case: No more options, so break out of the loop.
         break
   esac

   shift
done

###############################################################################
###############################################################################
# Option after check
if [ -z "${ENV_DATA}" ]; then
   show_help    # Display a usage synopsis.
   die 'ERROR: "--env <env_data>" required.'
fi

if [ ! -r "${ENV_DATA}" ]; then
	die "\`${ENV_DATA}\' unreadable"
fi


if [ -z "${RELEASE_VERSION}" ]; then
   show_help    # Display a usage synopsis.
   die 'ERROR: "--release-version VxxRxx" required.'
fi

if [ ! -z "${OPT_VERBOSE}" ]; then
   printf "Verbose Level: ${OPT_VERBOSE}\n"
fi

RELEASE_VERSION=`echo $RELEASE_VERSION | tr '[:lower:]' '[:upper:]'`
TEST=`echo $RELEASE_VERSION | sed "s/^V[0-9][0-9]R[0-9][0-9]$//i"`

if [ ! -z "${TEST}" ]; then
   show_help    # Display a usage synopsis.
   die "Wrong parameter for software release version .. Bye."
fi

###############################################################################
###############################################################################
# OPTION PARAMETERS
CYGPATH_OPT=-u

###############################################################################
###############################################################################
# Definitions
DEFINE_FILEOBJ EXE CYGPATH_EXE   /bin/cygpath
#DEFINE_FILEOBJ EXE ECD_EXE $(MCU_TOOLS_HOME)/../eclipse/ecd.exe
DEFINE_FILEOBJ RO LINT_PROJECT_PATH `${CYGPATH_EXE} ${CYGPATH_OPT} 'L:\LNT'`
DEFINE_FILEOBJ EXE LINT_EXE      `which lint-nt.exe`
DEFINE_FILEOBJ EXE GCC_EXE       /bin/i686-w64-mingw32-gcc

DEFINE_FILEOBJ EXE CP_EXE        /bin/cp
DEFINE_FILEOBJ EXE MV_EXE        /bin/mv
DEFINE_FILEOBJ EXE MMV_EXE       /bin/mmv
DEFINE_FILEOBJ EXE RM_EXE        /bin/rm
DEFINE_FILEOBJ EXE CAT_EXE       /bin/cat
DEFINE_FILEOBJ EXE AWK_EXE       /bin/awk
DEFINE_FILEOBJ EXE SED_EXE       /bin/sed
DEFINE_FILEOBJ EXE GREP_EXE      /bin/grep
DEFINE_FILEOBJ EXE TR_EXE        /bin/tr
DEFINE_FILEOBJ EXE SORT_EXE      /bin/sort
DEFINE_FILEOBJ EXE FIND_EXE      /bin/find
DEFINE_FILEOBJ EXE HEAD_EXE      /bin/head
DEFINE_FILEOBJ EXE XARGS_EXE     /bin/xargs
DEFINE_FILEOBJ EXE DOS2UNIX_EXE  /bin/dos2unix
DEFINE_FILEOBJ EXE UNIFDEF_EXE   /bin/unifdef
DEFINE_FILEOBJ EXE DOXYGEN_EXE   `which doxygen`
DEFINE_FILEOBJ EXE SUBST_EXE     `which subst`
DEFINE_FILEOBJ EXE SVN_EXE       `which svn`

DEFINE_FILEOBJ RO  SED_PREPROC_ARGS `${CYGPATH_EXE} ${CYGPATH_OPT} 'L:/SCRIPTS/sed_preprocess_args.txt'`

###############################################################################
###############################################################################
# SOURCE CODE GENERATION - C FILES
# 26.07.2017@mvh: not required, part of makefile.target ${DOS2UNIX_EXE} ${ENV_DATA}

ENV_DATA_START_MAKER=`grep "###START_ENV_DATA###" ${ENV_DATA}`
ENV_DATA_END_MAKER=`grep "###END_ENV_DATA###" ${ENV_DATA}`

# ENV_DATA plausibility check
if [ -z "${ENV_DATA_START_MAKER}" ] || [ -z "${ENV_DATA_END_MAKER}" ]; then
   die "ERROR: Missing start or end marker in file \`${ENV_DATA}\'. Bye."
fi

. ${ENV_DATA}

BUILD_ENV_LIST="\
   BUILD_DEVICE \
   PROJDIRPATH \
   LINKER_FILE \
   SHIP_BASE_PATH \
   SHIP_DOC_PATH \
   SHIP_LIB_PATH \
   SHIP_LNK_PATH \
   SHIP_OUT_PATH \
   SHIP_SRC_PATH \
   SHIP_TEST_PATH \
   ORIGIN_OUT_DIR \
   ORIGIN_LIB_DIR \
   RELEASE_NAME \
   SVNLOC SVNREV \
   BUILD_DIR \
   PROJ_INCLUDES \
   SYS_INCLUDES \
   BUILD_ARTIFACT_FILE_BASE \
   SHIP_FILES \
   SHIP_C_SRCS \
   LINT_PROJECT_PATH \
   LINT_OPTION_FILES \
   LINT_FILES \
   LINT_INCLUDES \
   LINT_MISRA_C \
"

for string in ${BUILD_ENV_LIST}; do
   eval "value=\$$string"
   CHECK_FILEOBJ STR "${string}" "${value}"
done

#${SUBST_EXE} | ${GREP_EXE} -E "^L:" | ${AWK_EXE} -F'=>' '{print $2}' 
DRIVE_L=`${SUBST_EXE} | ${GREP_EXE} -E "^L:" | ${AWK_EXE} -F'=>' '{print $2}' | sed 's#\\\#/#g' | ${XARGS_EXE} -iXX ${CYGPATH_EXE} ${CYGPATH_OPT} 'XX'`
CHECK_RESULT "GET_DRIVE_L"
print_debug 2 "Drive L:    ${DRIVE_L}"

# Check wether drive L is mapped correctly
TEST_DIR=${SVNLOC}
print_debug 2 "TEST_DIR:   $TEST_DIR"
if [ "${TEST_DIR}" -ef "${DRIVE_L}" ]; then
   die "ERROR: ${TEST_DIR} != ${DRIVE_L}. Bye."
fi

DRIVE_M=`${SUBST_EXE} | ${GREP_EXE} -E "^M:" | ${AWK_EXE} -F'=>' '{print $2}' | sed 's#\\\#/#g' | ${XARGS_EXE} -iXX ${CYGPATH_EXE} ${CYGPATH_OPT} 'XX'`
CHECK_RESULT "GET_DRIVE_M"
print_debug 2 "Drive M: => ${DRIVE_M}"

# Check wether drive M is mapped correctly
TEST_DIR="${SVNLOC}/SHIP"
print_debug 2 "TEST_DIR:   $TEST_DIR"
if [ "${TEST_DIR}" -ef "${DRIVE_M}" ]; then
   die "ERROR: ${TEST_DIR} != ${DRIVE_M}. Bye."
fi

###############################################################################
###############################################################################

SVN_WC_ROOT="`svn info --show-item wc-root /cygdrive/c/DATA/SVN/JST/jst_bentley_gauges_sw/branches/DevCOMPASS`/trunk"
if [ -z ${SVN_WC_ROOT} ]; then
   die "Unable to determine SVN WC-Root"
fi

SVN_ROOT_URL=`svn info --show-item repos-root-url /cygdrive/c/DATA/SVN/JST/jst_bentley_gauges_sw/branches/DevCOMPASS`
if [ -z ${SVN_ROOT_URL} ]; then
   die "Unable to determine SVN root url"
fi

SEARCH_LIST_DOC="\
 Design \
 Design/SW_A_Architecture \
 Design/SW_FD_Fine_Designs/SW_FD_JST_BY634_5_* \
 Design/SW_SPEC_Parameter_Specification \
"

SEARCH_LIST_TEST="\
 Test/LIN_Conformance_Test/*${RELEASE_VERSION} \
 Test/RAM_ROM_Usage/*${RELEASE_VERSION} \
 Test/Runtime_Measurement/*${RELEASE_VERSION} \
 Test/System_Test_MANUALLY/*${RELEASE_VERSION}* \
"

FIND_OPTS="-maxdepth 1 ! -type d"

IGNORE_FILTER_CLOCK='(COMPASS|OAT|STOPWATCH|GAUGES)'
IGNORE_FILTER_COMPASS='(CLOCK|OAT|STOPWATCH)'
IGNORE_FILTER_OAT='(CLOCK|COMPASS|STOPWATCH)'
IGNORE_FILTER_STOPWATCH='(CLOCK|COMPASS|OAT)'

###############################################################################
###############################################################################

cd "${BUILD_DIR}"

if [ ! -z "${OPT_NO_SOURCES}" ]; then
   printf "# Skipping sources creation due to option --no-sources\n"
elif [ ! -z "${OPT_NO_C_SOURCES}" ]; then
   printf "# Skipping sources creation due to option --no-c-sources\n"
else
   printf "###############################################################################\n"
   echo Creating new sources in ${SHIP_SRC_PATH} - C SOURCE FILES
   
   SHIP_FILES=`echo ${SHIP_FILES} | sed -e s/_c\.c/.c/g`
   print_debug 2 "${SHIP_FILES}"
   SHIP_GCC_ARGS_FILES=`echo ${SHIP_FILES} | sed -e s/\.c/.gcc.args/g`
   print_debug 2 "${SHIP_GCC_ARGS_FILES}"
   if [ "$OPT_VERBOSE" > "1" ]; then
      echo ${SHIP_FILES}
   fi

   for c_org_file in ${SHIP_FILES}; do
      c_file=`${CYGPATH_EXE} ${CYGPATH_OPT} ${BUILD_DIR}/${c_org_file}`

      defs_file=`echo -n ${c_file} | sed -e "s/\.c$/.defs/g"`
      args_file=`echo -n ${c_file} | sed -e "s/\.c$/.args/g"`
      CHECK_FILEOBJ RO "ArgsFile" ${args_file}
      gcc_args_file=`echo -n ${c_file} | sed -e "s/\.c$/.gcc.args/g"`
      print_debug 1 "\t${gcc_args_file}" 

      ${GREP_EXE} -v "^[\s]*-[^iI]" ${args_file} | \
         ${TR_EXE} -d "\n" | \
         ${SED_EXE} -f `echo ${SED_PREPROC_ARGS}` | \
         ${GREP_EXE} -v "^-I-" | \
         ${SED_EXE} -e "s#^-I##" | sed -e "#^$#d" | \
         ${SORT_EXE} ${CYGPATH_OPT} -o ${gcc_args_file}1
      ${DOS2UNIX_EXE} -q ${gcc_args_file}1
      rm -f ${gcc_args_file}
      for orgdir in `${CAT_EXE} ${gcc_args_file}1`; do
         newdir=`${CYGPATH_EXE} ${CYGPATH_OPT} ${orgdir}`
         echo -I${newdir} >> ${gcc_args_file}
      done

      print_debug 1 "\t${defs_file}" 
      ${GCC_EXE} -E -dM -DSVN_REVISION=${SVNREV} -DSVN_LOCATION=${SVNLOC} -DDEBUG_DEVELOPMENT=0 @${gcc_args_file} -o ${defs_file} ${PROJDIRPATH}/${c_org_file}
      CHECK_RESULT "C_SOURCES__GCC_CREATE_DEF_FILE"
      
      printf "\t${SHIP_SRC_PATH}/`basename ${c_file}`\n" 
      ${UNIFDEF_EXE} -DSVN_REVISION=${SVNREV} -DSVN_LOCATION=${SVNLOC} -f ${defs_file} ${PROJDIRPATH}/${c_org_file} > ${SHIP_SRC_PATH}/`basename ${c_file}`
      CHECK_RESULT_2 "C_SOURCES__UNIFDEF_REMOVE_UNUSED_DEFINES"

      ${SED_EXE} -i "/^\(#line.*\)\?\$/d" ${SHIP_SRC_PATH}/`basename ${c_file}`
      CHECK_RESULT "C_SOURCES__SED_LINE"
      ${SED_EXE} -i "/^.*file.*\$HeadURL.*\$/d" ${SHIP_SRC_PATH}/`basename ${c_file}`
      CHECK_RESULT "C_SOURCES__SED_HEADURL"

      print_debug 1 "########\n"
   done
fi

if [ ! -z "${OPT_NO_SOURCES}" ]; then
   printf "# Skipping sources creation due to option --no-sources\n"
elif [ ! -z "${OPT_NO_H_SOURCES}" ]; then
   printf "# Skipping sources creation due to option --no-h-sources\n"
else
   ###############################################################################
   ###############################################################################
   # SOURCE CODE GENERATION - H FILES
   printf "###############################################################################\n"
   echo Creating new sources in ${SHIP_SRC_PATH} - HEADER FILES

   GCC_ARGS_FILE=${BUILD_DIR}/COMMON_BSW/main.gcc.args
   TMP_DIRNAME=/tmp/jst_`date +%s`
   #NOT_REQ TMP_H_FILE=$TMP_DIRNAME/filelist.h.txt

   if [ ! -f "$GCC_ARGS_FILE" ]; then
      echo GCC_ARGS_FILE missing
      exit 1
   fi

   if [ ! -d "$SHIP_BASE_PATH" ]; then
      echo SHIP_BASE_PATH invalid!
      exit 1
   fi

   ###############################################################################

   SHIP_SRC_PATH=$SHIP_BASE_PATH/SRC

   mkdir -p $TMP_DIRNAME
   # Removing windows \\r from $GCC_ARGS_FILE ..
   #NOT_REQ ${SED_EXE} -ie 's/\r//g' $GCC_ARGS_FILE
   #NOT_REQ CHECK_RESULT "H_SOURCES__SED_LINE_1"

   ### SYS_INCLUDES
   # TODO SYS_INCLUDES aus PFAD EINSAMMELN
   #${CAT_EXE} $GCC_ARGS_FILE | ${SED_EXE} "s/^-I//g"| ${XARGS_EXE} ${CYGPATH_EXE} ${CYGPATH_OPT} | ${XARGS_EXE} -iXX ${FIND_EXE} XX -iname *.h > $TMP_H_FILE
   H_FILES=`${FIND_EXE} ${PROJ_INCLUDES} ${SYS_INCLUDES} -maxdepth 1 -type f -iname "*.h" # | grep -v "adv64.h"`
   CHECK_RESULT "H_SOURCES__SED_LINE_2"

   if [ -z "${H_FILES}" ]; then
      die "ERROR: no h files found. Bye."
   fi

   for file in ${H_FILES}; do
      BASEFILE=`basename $file .h`
      DEFSFILE=${TMP_DIRNAME}/${BASEFILE}.defs
      TARGETFILE=${SHIP_SRC_PATH}/`basename ${file}`
      printf "\t${file} -> ${TARGETFILE}\n"

      if [ "${BASEFILE}" = "adv64.h" ]; then
         # Header define (FILE_H) must be excluded
         REMOVE_DEF=`${CAT_EXE} ${file} | ${GREP_EXE} "^#define"| ${HEAD_EXE} -n 1| ${SED_EXE} 's/^#define[ \t]\+//g'| ${SED_EXE} 's/\r//g'`
         CHECK_RESULT "H_SOURCES__SED_LINE_3"

         print_debug 1 "\tDefinitions / REMOVE: ${REMOVE_DEF}\n"

         # Collecting all defines from header file
         print_debug 1 "\tDefinitions / FILE  : ${DEFSFILE}\n"
         ${GCC_EXE} -E -dM -DSVN_REVISION=${SVNREV} -DSVN_LOCATION=${SVNLOC} -DDEBUG_DEVELOPMENT=0 @${GCC_ARGS_FILE} ${file} > ${DEFSFILE}
         CHECK_RESULT "H_SOURCES__GCC_CREATE_DEF_FILE"

         # remove FILE_H definition from defines
         ${SED_EXE} -ie "/${REMOVE_DEF}/d" ${DEFSFILE}
         CHECK_RESULT "H_SOURCES__SED_LINE_4"
         ${SED_EXE} -ie "s/\r//g" ${DEFSFILE}
         CHECK_RESULT "H_SOURCES__SED_LINE_5"

         # removing obsolete definitions
         ${UNIFDEF_EXE} -DSVN_REVISION=${SVNREV} -DSVN_LOCATION=${SVNLOC} -f $DEFSFILE ${file} > ${TARGETFILE}
         CHECK_RESULT_2 "H_SOURCES__UNIFDEF_REMOVE_UNUSED_DEFINES"

         ${SED_EXE} -i "/^.*file.*${HeadURL}.*$/d" ${TARGETFILE}
         CHECK_RESULT "H_SOURCES__SED_LINE_6"
      else
         ${CP_EXE} ${COPY_OPTS} ${file} ${TARGETFILE}
         CHECK_RESULT "H_SOURCES__COPY_FILE"
      fi

      print_debug 1 "########\n"
   done

   ###############################################################################

   rm -rf ${TMP_DIRNAME}
   CHECK_RESULT "REMOVE_TMP_FILE"
fi
 
if [ ! -z "${OPT_NO_SOURCES}" ]; then
   printf "# Skipping sources creation due to option --no-sources\n"
elif [ ! -z "${OPT_NO_DOXY_SOURCES}" ]; then
   printf "# Skipping sources creation due to option --no-doxy-sources\n"
else
   ###############################################################################
   printf "#Looking for doxygen files and copy them ..\n"
   ${FIND_EXE} ${SVNLOC}/SRC -iname *.doxy
   ${FIND_EXE} ${SVNLOC}/SRC -iname *.doxy -exec ${CP_EXE} ${COPY_OPT} {} $SHIP_SRC_PATH \;
   CHECK_RESULT "DOXY_FILES"
   printf "#fin\n"

   printf "Preprocessing sources done.\n"

fi # NO_SOURCES

###############################################################################
###############################################################################

if [ ! -z "${OPT_NO_LINT}" ]; then
   printf "# Skipping lint report generation due to option --no-lint\n"
else
   printf "###############################################################################\n"
   echo Execute Project-PC-Lint:
   
   LINT_OUT_FILE_PATH="`${CYGPATH_EXE} -u ${SHIP_OUT_PATH}/../..`"
   LINT_OUT_FILE_NAME="`basename ${BUILD_ARTIFACT_FILE_BASE}`.lint"
   LINT_OUT_FILE_PATH_DOS="`${CYGPATH_EXE} -m ${LINT_OUT_FILE_PATH}`"
   LINT_SRC=${LINT_OUT_FILE_PATH}/${LINT_OUT_FILE_NAME}
   if [ "$OPT_VERBOSE" > "1" ]; then
      printf "\tOutput: ${LINT_OUT_FILE_PATH}/${LINT_OUT_FILE_NAME}\n"
   fi

   SHIP_C_SRCS=`echo ${SHIP_C_SRCS} | sed -e s/_c\.c/.c/g`
   print_debug 2 "${SHIP_C_SRCS}"

   # Check existence of source files
   for file in ${SHIP_C_SRCS}; do
      CHECK_FILEOBJ RO "LintSourceFile" ${file}
   done
   

   if [ "$OPT_VERBOSE" > "2" ]; then
      echo ${LINT_EXE} \
         -i`${CYGPATH_EXE} -m ${LINT_PROJECT_PATH}` \
         -DSVN_REVISION=${SVNREV} \
         -DSVN_LOCATION=`${CYGPATH_EXE} -m ${SVNLOC}` \
         -os"(${LINT_OUT_FILE_PATH}/${LINT_OUT_FILE_NAME})" \
         ${LINT_OPTION_FILES} \
         -i`${CYGPATH_EXE} -m ${SHIP_SRC_PATH}` \
         ${SHIP_C_SRCS} \
         --header"(co-lisa_s12z.h)" \
         +vf
   fi

   ${LINT_EXE} \
      -i`${CYGPATH_EXE} -m ${LINT_PROJECT_PATH}` \
      -DSVN_REVISION=${SVNREV} \
      -DSVN_LOCATION=`${CYGPATH_EXE} -m ${SVNLOC}` \
      -os"(`${CYGPATH_EXE} -m ${LINT_OUT_FILE_PATH}/${LINT_OUT_FILE_NAME}`)" \
      ${LINT_OPTION_FILES} \
      -i`${CYGPATH_EXE} -m ${SHIP_SRC_PATH}` \
      ${SHIP_C_SRCS} \
      --header"(co-lisa_s12z.h)" \
      +vf
   CHECK_RESULT "PC_LINT"

   echo Linting done.

   printf "\tCreating LINT report .. \n"
   CHECK_FILEOBJ RO "LintReport" ${LINT_SRC}
   LINT_REPORT="${SHIP_DOC_PATH}/JST_BY634_5_LINT_REPORT_${BUILD_DEVICE}_${RELEASE_VERSION}.txt"

   if [ ! -f "${LINT_SRC}" ]; then
      printf "Lint report file missing. Bye\n"
      exit 1
   else
      printf "\tUsing LINT report: ${LINT_SRC}\n"
   fi

   #LINT_ERROR=`cat  ${LINT_SRC} | grep -ie "error[ \t]*[0-9]\+"`
   #if [ ! -z "${LINT_ERROR}" ]; then
   #   die "Error while executing Lint. Bye."
   #fi

   WARN_CNT=`cat ${LINT_SRC} | ${GREP_EXE} -i required | ${GREP_EXE} -v "Isr_VectorTable.c" | wc -l`
   echo "LINT REPORT" > ${LINT_REPORT}
   echo "===========" >> ${LINT_REPORT}
   echo 'Project: JST BY 634/5' >> ${LINT_REPORT}
   echo "Device:  ${BUILD_DEVICE}"  >> ${LINT_REPORT}
   echo "Version: ${RELEASE_VERSION}" >> ${LINT_REPORT}
   echo ""  >> ${LINT_REPORT}
   echo "Number of errors:  ${WARN_CNT}"  >> ${LINT_REPORT}
   echo ""  >> ${LINT_REPORT}
   echo "List of Errors" >> ${LINT_REPORT}
   echo "==============" >> ${LINT_REPORT}
   ${CAT_EXE} ${LINT_SRC} | ${GREP_EXE} -i required | ${GREP_EXE} -v "Isr_VectorTable.c" >> ${LINT_REPORT}
   CHECK_RESULT_2 "LINT_REPORT_FINAL"
   #rm -fv $SHIP_OUT_PATH/JST_BY_RELEASE_${BUILD_DEVICE}_S12Z_VHL64.lint

fi ## NO_LINT

###############################################################################
###############################################################################
if [ ! -z "${OPT_NO_DOXYGEN}" ]; then
   printf "# Skipping doxygen generation due to option --no-doxygen\n"
else
   printf "###############################################################################\n"
   echo Creating doxygen documentation
   ${DOXYGEN_EXE} L:/DOC/JST_BY634_5_${BUILD_DEVICE}.doxyfile
   CHECK_RESULT "DOXYGEN"
fi # NO_DOXYGEN

if [ ! -z "${OPT_NO_LATEX}" ]; then
   printf "# Skipping LaTeX generation due to option --no-doxygen\n"
else
   echo Creating LaTeX documentation
   ${RM_EXE} -f ${SHIP_DOC_PATH}/${RELEASE_NAME}.pdf
   CHECK_RESULT "REMOVE_PDF_FILE"
   ${SHIP_DOC_PATH}/latex/make.bat
   CHECK_RESULT "CREATE_DOC_PDF"
fi # NO_LATEX

###############################################################################
###############################################################################
if [ ! -z "${OPT_NO_DOC_COPY}" ]; then
   printf "# Skipping document copying due to option --no-doc-copy\n"
else
   printf "###############################################################################\n"
   printf "Copy link file ...\n"
   ${CP_EXE} ${COPY_OPT} ${LINKER_FILE} ${SHIP_LNK_PATH}
   CHECK_RESULT "COPY_1"
   echo Copy libs and binaries ...
   ${CP_EXE} ${COPY_OPT} ${ORIGIN_OUT_DIR}/${RELEASE_NAME}.elf* ${SHIP_OUT_PATH}
   CHECK_RESULT "COPY_2"
   ${CP_EXE} ${COPY_OPT} ${ORIGIN_OUT_DIR}/${RELEASE_NAME}.map ${SHIP_OUT_PATH}
   CHECK_RESULT "COPY_3"
   ${CP_EXE} ${COPY_OPT} ${ORIGIN_OUT_DIR}/${RELEASE_NAME}.sap ${SHIP_OUT_PATH}
   CHECK_RESULT "COPY_4"
   ${CP_EXE} ${COPY_OPT} ${ORIGIN_OUT_DIR}/${RELEASE_NAME}.sx ${SHIP_OUT_PATH}
   CHECK_RESULT "COPY_5"
   ${CP_EXE} ${COPY_OPT} ${ORIGIN_LIB_DIR}/LIB_MCAL.lib ${SHIP_LIB_PATH}
   CHECK_RESULT "COPY_6"
   ${CP_EXE} ${COPY_OPT} ${ORIGIN_LIB_DIR}/LIB_MCAL.lst ${SHIP_LIB_PATH}
   CHECK_RESULT "COPY_7"
   ${CP_EXE} ${COPY_OPT} ${ORIGIN_LIB_DIR}/JST_BY_RELEASE_LIB_${BUILD_DEVICE}.lib ${SHIP_LIB_PATH}
   CHECK_RESULT "COPY_8"
   ${CP_EXE} ${COPY_OPT} ${ORIGIN_LIB_DIR}/JST_BY_RELEASE_LIB_${BUILD_DEVICE}.lst ${SHIP_LIB_PATH}
   CHECK_RESULT "COPY_9"
   if [ ! -z "${OPT_NO_LATEX}" ]; then
      printf "# Skipping copy of LaTeX documentation due to option --no-latex.\n"
   else
      ${CP_EXE} ${COPY_OPT} ${SHIP_DOC_PATH}/latex/refman.pdf ${SHIP_DOC_PATH}/${RELEASE_NAME}.pdf
      CHECK_RESULT "COPY_10"
      
      rm -rf ${SHIP_DOC_PATH}/html ${SHIP_DOC_PATH}/latex

      ${MV_EXE} -f "${SHIP_DOC_PATH}/JST_BY_RELEASE_${BUILD_DEVICE}_S12Z_VHL64.pdf" ${SHIP_DOC_PATH}/SW_DOC_JST_BY634_5_${BUILD_DEVICE}_RELEASE_${RELEASE_VERSION}.pdf
      CHECK_RESULT "COPY_11"
   fi

   ###############################################################################
   ###############################################################################
   printf "###############################################################################\n"

   printf "Device: ${BUILD_DEVICE}\n"

   ignorefilter="IGNORE_FILTER_${BUILD_DEVICE}"

   printf "\tCopy documentation ..\n"
   pushd . >/dev/null
   cd ${SVN_WC_ROOT}

   print_debug 2 "${FIND_EXE} ${SEARCH_LIST_DOC} ${FIND_OPTS} -iname *.pdf \| ${GREP_EXE} -viE ${!ignorefilter}"
   PDF_LIST=`${FIND_EXE} ${SEARCH_LIST_DOC} ${FIND_OPTS} -iname *.pdf | ${GREP_EXE} -viE "${!ignorefilter}"`
   CHECK_RESULT_2 "COPY_DOCUMENTS_DOC_CREATE_LIST"
   print_debug 2 ${PDF_LIST}

   COPY_CNT="0"
   for pdf in ${PDF_LIST}; do
      ${CP_EXE} ${COPY_OPT} ${pdf} ${SHIP_DOC_PATH}/
      CHECK_RESULT "COPY_DOCUMENTS_DOC"
      COPY_CNT=$((COPY_CNT + 1))  # Each -v adds 1 to verbosity.
   done
   printf "\t${COPY_CNT} files copied.\n"

   printf "\tCopy test results ..\n"
   PDF_LIST=`${FIND_EXE} $SEARCH_LIST_TEST $FIND_OPTS -iname *.pdf | ${GREP_EXE} -viE ${!ignorefilter}`
   CHECK_RESULT_2 "COPY_DOCUMENTS_TEST_CREATE_LIST"
   
   COPY_CNT="0"
   for pdf in ${PDF_LIST}; do
      ${CP_EXE} ${COPY_OPT} ${pdf} ${SHIP_TEST_PATH}/
      CHECK_RESULT "COPY_DOCUMENTS_TEST"
      COPY_CNT=$((COPY_CNT + 1))  # Each -v adds 1 to verbosity.
   done
   printf "\t${COPY_CNT} files copied.\n"

   ${MMV_EXE} -vd "${SHIP_LIB_PATH}/LIB_MCAL.*" "${SHIP_LIB_PATH}/JST_BY634_5_LIB_MCAL_${RELEASE_VERSION}.#1"
   CHECK_RESULT "COPY_MMV_1"
   ${MMV_EXE} -vd "${SHIP_LIB_PATH}/JST_BY_RELEASE_LIB_${BUILD_DEVICE}.*" "${SHIP_LIB_PATH}/JST_BY634_5_LIB_${BUILD_DEVICE}_${RELEASE_VERSION}.#1"
   CHECK_RESULT "COPY_MMV_2"
   ${MMV_EXE} -vd "${SHIP_OUT_PATH}/JST_BY_RELEASE_*_S12Z_VHL64.*" "${SHIP_OUT_PATH}/JST_BY634_5_#1_REL_${RELEASE_VERSION}_S12Z_VHL64.#2"
   CHECK_RESULT "COPY_MMV_3"

   popd
fi # NO_DOC_COPY

###############################################################################
printf "############\n"
if [ -z "${OPT_NO_LINT}" ]; then
   printf "Please check LINT report for plausibility\n"
fi
printf "### END ###\n"
###############################################################################

