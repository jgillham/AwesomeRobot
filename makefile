README.html: README.md
	echo "<html><head><meta content=\"text/html; charset=ISO-8859-1\" http-equiv=\"content-type\"><title></title></head><body>" > $@
	cat README.md >> $@
	echo "</body></html>" >> $@
	
