function getReaction(){

	// grabs the input from the user
	let input =  document.getElementById("salary").value;
	if (input == 2004) {
		document.getElementById("result-parent").style.visibility = "visible"
		document.getElementById("result-parent").style.color = "red"
		document.getElementById("result-parent").innerText = "Way to go Champ";
	}
	else{

		// makes the div visible
		document.getElementById("result-parent").style.visibility = "visible";
		// element.style can be used to change CSS properties of an HTML document
		document.getElementById("result-parent").style.color = "black"
		document.getElementById("result-parent").innerText = "Better luck next time Chief";
		
	}
	
}