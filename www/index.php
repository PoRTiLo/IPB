<?php

	require_once('connect.inc');

	
	$head = '<html>
				<head>
					<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
					<META HTTP-EQUIV="REFRESH" CONTENT="200">
					<link rel="stylesheet" href="css.css" type="text/css">
					<title>IPB</title>
				</head>'
	;
	$foot = '<div id="footer"><br>
				<p id="reason">Stránka vzniklá jako IPB, FIT-VUT Brno<span>|</span>  xsendl00,E-mail: <a href="mailto:xsendl00@stud.fit.vutbr.cz">xsendl00@stud.fit.vutbr.cz</a></p>
			</div>'
	;
	$query = "SELECT * from status;";
	$result = Pg_Exec($conn, $query);
	if( !$result )
	{
		echo "<h2>NEZISKALI JSM EDTA</h2>";
	}
	else
	{
		echo $head;
		echo "<body><table><tr><th>num.</th><th>JID</th><th>presence</th><th>icon</th><th>time</th><th>client</th><th>status</th></tr>";
		$num = 1;
		while( $row = Pg_Fetch_Array($result))
		{
			$img = showImg($row["presence"]);
			$client = showClient($row["resource"]);
			echo "<tr><td>".$num++."</td><td>".$row["jidbare"]."</td><td>".$row["presence"]."</td><td>".$img."</td><td>".$row["date"]."</td><td>".$row["status"]."</td></tr>";
		}
	}

	echo "</table>";
	echo $foot;
	echo "</body></html>";

	pg_close($conn);
	
	
	function showImg($status) {
		
		$img = "<img src='img/proto_jabber_002.png' width='16' height='16' />";
		if($status == "Available")
			$img = "<img src='img/proto_jabber_001.png' width='16' height='16' />";
		else if($status == "Unavaliable")
			$img = "<img src='img/proto_jabber_002.png' width='16' height='16' />";
		else if($status == "Away")
			$img = "<img src='img/proto_jabber_003.png' width='16' height='16' />";
		else if($status == "DND")
			$img = "<img src='img/proto_jabber_006.png' width='16' height='16' />";
		else if($status == "XA")
			$img = "<img src='img/proto_jabber_007.png' width='16' height='16' />";
		else if($status == "Probe")
			$img = "<img src='img/proto_jabber_005.png' width='16' height='16' />";
		else if($status == "Error")
			$img = "<img src='img/proto_jabber_008.png' width='16' height='16' />";
		else if($status == "Invalid")
			$img = "<img src='img/proto_jabber_005.png' width='16' height='16' />";
		else if($status == "Chat")
			$img = "<img src='img/proto_jabber_004.png' width='16' height='16' />";
		
		return $img;
	}
	
	function showClient($resource) {
		
		$client = "unknow";
		if($resource == "Available")
			$client = "<img src='img/proto_jabber_001.png' width='16' height='16' />";
		else if($resource == "Unavaliable")
			$client = "<img src='img/proto_jabber_002.png' width='16' height='16' />";
		else if($resource == "Available")
			$client = "<img src='img/jabber_online.png' width='128' height='128' />";
		else if($resource == "Available")
			$client = "<img src='img/jabber_online.png' width='128' height='128' />";
		return $client;
	}
?>
