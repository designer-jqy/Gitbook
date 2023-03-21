#!/bin/bash
MODEL={model_name}
PATH={log_path}
LOG_FILE=(api request error performance trace)

if [ -t 1 ]; then
  is_tty() {
    true
  }
else
  is_tty() {
    false
  }
fi

setupColor() {
  # Only use colors if connected to a terminal
  if is_tty; then
    RAINBOW="
      $(printf '\033[38;5;196m')
      $(printf '\033[38;5;202m')
      $(printf '\033[38;5;226m')
      $(printf '\033[38;5;082m')
      $(printf '\033[38;5;021m')
      $(printf '\033[38;5;093m')
      $(printf '\033[38;5;163m')
    "
    RED=$(printf '\033[31m')
    GREEN=$(printf '\033[32m')
    YELLOW=$(printf '\033[33m')
    BLUE=$(printf '\033[34m')
    BOLD=$(printf '\033[1m')
    RESET=$(printf '\033[m')
  else
    RAINBOW=""
    RED=""
    GREEN=""
    YELLOW=""
    BLUE=""
    BOLD=""
    RESET=""
  fi
}

fmtOutput()
{
    printf '%s%s: %s' ${GREEN} "$1" ${RESET}
    command "$2"
}

getPath()
{
    if [ ${MODEL} = model_name_1 ]; 
    then
      LOGPATH=model_name_1_relative_path
    elif [ ${MODEL} = model_name_2 ];
    then
      LOGPATH=model_name_2_relative_path
    elif [ ${MODEL} = model_name_3 ];
    then
      LOGPATH=model_name_3_relative_path
    fi
    cd "${PATH}/dev-${LOGPATH}/"

    fmtOutput 'Current path' pwd
}

cleanLog()
{
    for i in ${LOG_FILE[@]}
    do 
        printf '%s%-28s%s' ${RED} "Clean ${i}.log ..." ${RESET}
        > "${i}.log"
        echo "${GREEN}Complete${RESET}"
    done
}

main()
{
    while [ $# -gt 0 ]; do
       case $1  in
         model_name_1) MODEL=model_name_1;;
         model_name_2) MODEL=model_name_2;;
         model_name_3) MODEL=model_name_3;;
       esac
       shift
    done

    setupColor

    printf "%s %s%s%s\n" "Current Model:" ${RED} ${MODEL} ${RESET}
    getPath $1

    cleanLog
}


main "$@"
