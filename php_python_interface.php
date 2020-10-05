<?php

	$fp = fopen("./testcsv.csv", "r");
	$data = fgetcsv($fp,1000,",");

	echo "<form action='#' method='post'";

	echo "<div><select name='drop1'>";
	foreach ($data as $thing) {
		echo "<option value='".$thing."'>".$thing."</option>";
	} echo "</select></div>";

	echo "<div><select name='drop2'>";
	foreach ($data as $thing) {
		echo "<option value='".$thing."'>".$thing."</option>";
	} echo "</select></div>";

	echo "<input type='submit' name='submit' value='Submit' />";
	echo "</form>";

	fclose($fp);

	if (isset($_POST['submit'])) {
		$in1 = array_search($_POST['drop1'], $data);
		$in2 = array_search($_POST['drop2'], $data);
		print $_POST['drop1'].$_POST['drop2']."here";
		shell_exec("python3 corrplot.py testcsv.csv ".$in1." ".$in2);
	}


	// shell_exec("python3 corrplot.py testcsv.csv 0 1");

?>