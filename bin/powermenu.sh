rofi_command="rofi -theme ~/.config/rofi/themes/powermenu.rasi"

uptime=$(uptime -p | sed -e 's/up //g')

# Options
shutdown=""
reboot=""
lock=""
suspend=""
logout=""

# Variable passed to rofi
options="$logout\n$lock\n$shutdown\n$reboot\n$suspend"

chosen="$(echo -e "$options" | $rofi_command -p "UP - $uptime" -dmenu -selected-row 2)"
case $chosen in
	$shutdown)
		systemctl poweroff
		;;
   	$reboot)
		systemctl reboot
		;;
	$lock)
		betterlockscreen -l dimblur
		;;
    $suspend)
		systemctl suspend
		;;
    $logout)
		killall xinit
		;;
esac
