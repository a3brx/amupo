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
