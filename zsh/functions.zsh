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

function yt() {
    youtube-dl -x --audio-format mp3 --add-metadata --embed-thumbnail ytsearch:"$1" -o "~/Music/Tracks/%(title)s.%(ext)s"
}
