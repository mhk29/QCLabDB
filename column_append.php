<?php 

$delimiter = ",";
$csv_data = array();
$row = 0;
if (($handle = fopen('testcsv.csv', 'r')) !== FALSE) {
    while (($data = fgetcsv($handle, 1000, $delimiter)) !== FALSE) {
        $csv_data[] = $data;
        $row = $row + 1;
    }
    fclose($handle);
}

foreach ($csv_data as $i => $data) {
    $csv_data[$i] = $data = array_merge($data, $extra_columns);
}

if (($handle = fopen('testcsv.csv', 'w')) !== FALSE) {
    foreach ($csv_data as $data) {
        fputcsv($handle, $data, $delimiter);
    }
    fclose($handle);
}

?>