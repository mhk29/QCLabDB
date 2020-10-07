<?php

	$name = "./testcsv.csv";
	$fp = fopen($name, "r");
	$data = fgetcsv($fp,1000,",");

	echo "Plotter for ".$name;
	echo "<br /><br />";

	echo "<form action='#' method='post'";

	echo "<div>
		Column 1:
		<select name='drop1'>";
	foreach ($data as $thing) {
		echo "<option value='".$thing."'>".$thing."</option>";
	} echo "</select></div>";
	echo "<br /><br />";
	echo "<div>
		Column 2:
		<select name='drop2'>";
	foreach ($data as $thing) {
		echo "<option value='".$thing."'>".$thing."</option>";
	} echo "</select></div>";

	echo "<br /><br />";
	echo "<div><input type='submit' name='submit1' value='Linear' /></div>";
	echo "<br /><br />";
	echo "<div><input type='submit' name='submit1' value='Violin' /></div>";
	echo "</form>";

	fclose($fp);

	if (isset($_POST['submit1'])) {
		$in1 = array_search($_POST['drop1'], $data);
		$in2 = array_search($_POST['drop2'], $data);
		shell_exec("python3 corrplot.py testcsv.csv ".$in1." ".$in2);
	}

	if (isset($_POST['submit2'])) {
		$in1 = array_search($_POST['drop1'], $data);
		$in2 = array_search($_POST['drop2'], $data);
		shell_exec("python3 corrplot.py testcsv.csv ".$in1." ".$in2);
	}



	// shell_exec("python3 corrplot.py testcsv.csv 0 1");

?>