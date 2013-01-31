map KK :call H()

function H()
	echo system('echo -n $(h '.expand("<cword>").' 2> /dev/null)')
endfunction
