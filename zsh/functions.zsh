function tk() {
  mkdir -p $@ && cd ${@:$#}
}

function gx() {
    git add .
    if [ "$1" != "" ]
    then
        git commit -m "$1"
    else
        git commit -m update
    fi
    git push && git push gitlab
}
