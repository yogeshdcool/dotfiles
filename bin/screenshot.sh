rofi_command="rofi -theme ~/.config/rofi/themes/powermenu.rasi"

# Options
screen=""
area=""
window=""

# Variable passed to rofi
options="$window\n$screen\n$area"

chosen="$(echo -e "$options" | $rofi_command -p 'scrot' -dmenu -selected-row 1)"
case $chosen in
    $screen)
		sleep 1; scrot 'screenshot_%Y-%m-%d-%S_$wx$h.png' -e 'mv $f ~/Pictures/screenshots/ ; feh ~/Pictures/screenshots/$f'
        ;;
    $area)
		scrot -s 'screenshot_%Y-%m-%d-%S_$wx$h.png' -e 'mv $f ~/Pictures/screenshots/ ; feh ~/Pictures/screenshots/$f'
        ;;
    $window)
		sleep 1; scrot -u 'screenshot_%Y-%m-%d-%S_$wx$h.png' -e 'mv $f ~/Pictures/screenshots/ ; feh ~/Pictures/screenshots/$f'
        ;;
esac

