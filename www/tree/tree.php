<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head> 
    <title>Menu</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <link href="data/styles.css" rel="STYLESHEET" type="text/css">
    <script type="text/javascript" src="data/mootools.js"></script>
</head>
<body>
<div id="tree">
<?php
define("ROOT", "./cms/");

process_dir(ROOT);

function process_dir($dir, $name="")
{
    $dir=$dir.$name;
    slash(&$dir);
    if (contains_dir($dir)) {
        if ($dir!=ROOT) {
            echo "<p class='open'><a href='$dir'>".$name."</a></p>";
            echo "<div>";
        }
        $d=dir($dir);
        while ($f=$d->read()) {
            if (skip($f)) continue;
            if (is_dir($dir.$f)) process_dir($dir, $f);
        }
        if ($dir!=ROOT)
            echo "</div>";
    }
    else {
        if ($dir!=ROOT) echo "<p><a href='$dir'>".$name."</a></p>";
    }
}
function contains_dir($dir)
{
    slash(&$dir);
    $d=dir($dir);
    while ($f=$d->read()) {
        if (skip($f)) continue;
        if (is_dir($dir.$f)) return true;
    }

    return false;
}

function skip($f)
{
    return ($f=="." || $f=="..");
}
function slash($s)
{
    if (!ereg("/$", $s)) 
        $s=$s."/";
}
?>
</div>
<script type="text/javascript" src="data/js.js"></script>
</body>
</html>
