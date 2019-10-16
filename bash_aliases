# Working with repositories
create () {
	git init "$1"
	cd "$1"
}
clone () {
	# Creates a clone of a github repository and changes to the local directory
	git clone https://github.com/a3brx/$1.git
	cd "$1"
}
commit () {
	git add *
	git commit -m "$1"
	git remote rm origin
	git remote add origin https://github.com/a3brx/${PWD##*/}.git
	git push origin master	
}
alias remove='git rm'

rie () {
	if [ -d "$1" ]; then rm -rf "$1"; fi 2>/dev/null
}
alias delete='cd ~ && rie AEDA && rie FIS2 && rie LCOM && rie MNUM && rie TCOM'
alias quit='delete && rie Programs && rie .local && rie .cache'

# LCOM
alias lcom='unzip /opt/ucso/MINIX-LCOM.zip -d /tmp/ && VBoxManage startvm MINIX-LCOM --type headless && clear && ssh lcom@127.0.0.1 -p 2222'

# To start programs
alias clion='./~/AEDA/CLion/bin/clion.sh'
alias sublime='~/Programs/sublime_text/sublime_text'
alias gdrive='./gdrive'
