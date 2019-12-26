<html>
	<head>
		<title>Tugas RPL - Function Point</title>
	</head>

<body>

	<center>	
	<h1>Aplikasi Perhitungan <i>Function Point</i></h1>
	<marquee>oleh Radical Rakhman Wahid</marquee>
	
	<h4><i>Information Domain Values</i> (bilangan cacah)</h4>
	<i>*kotak kiri kategori mudah, tengah kategori sedang, dan kanan kategori rumit</i><br><br>
	
	<form action="" method="post">
	<i>External Input</i>:<br>
	<input type="text" name="EIm" value="<?=isset($_POST['EIm']) ? $_POST['EIm'] : ''?>"/> <input type="text" name="EIs" value="<?=isset($_POST['EIs']) ? $_POST['EIs'] : ''?>"/> <input type="text" name="EIr" value="<?=isset($_POST['EIr']) ? $_POST['EIr'] : ''?>"/><br><br>
	<i>External Output</i>:<br>
	<input type="text" name="EOm" value="<?=isset($_POST['EOm']) ? $_POST['EOm'] : ''?>"/> <input type="text" name="EOs" value="<?=isset($_POST['EOs']) ? $_POST['EOs'] : ''?>"/> <input type="text" name="EOr" value="<?=isset($_POST['EOr']) ? $_POST['EOr'] : ''?>"/><br><br>
	<i>Internal Logical File</i>:<br>
	<input type="text" name="ILFm" value="<?=isset($_POST['ILFm']) ? $_POST['ILFm'] : ''?>"/> <input type="text" name="ILFs" value="<?=isset($_POST['ILFs']) ? $_POST['ILFs'] : ''?>"/> <input type="text" name="ILFr" value="<?=isset($_POST['ILFr']) ? $_POST['ILFr'] : ''?>"/><br><br>
	<i>External Interface File</i>:<br>
	<input type="text" name="EIFm" value="<?=isset($_POST['EIFm']) ? $_POST['EIFm'] : ''?>"/> <input type="text" name="EIFs" value="<?=isset($_POST['EIFs']) ? $_POST['EIFs'] : ''?>"/> <input type="text" name="EIFr" value="<?=isset($_POST['EIFr']) ? $_POST['EIFr'] : ''?>"/><br><br>
	<i>External Inquiry</i>:<br>
	<input type="text" name="EInm" value="<?=isset($_POST['EInm']) ? $_POST['EInm'] : ''?>"/> <input type="text" name="EIns" value="<?=isset($_POST['EIns']) ? $_POST['EIns'] : ''?>"/> <input type="text" name="EInr" value="<?=isset($_POST['EInr']) ? $_POST['EInr'] : ''?>"/><br><br>

	<h4><i>Value Adjustment Factor</i></h4>
	
	<i>Data communications</i>:
	<select name="DC">
			<?php $oDC = array(0,1,2,3,4,5);
			foreach ($oDC as $DC) {
				$sDC = @$_POST['DC'] == $DC ? ' selected="selected"' : '';
				echo '<option value="' . $DC . '"' . $sDC . '>' . $DC . '</option>';
			}?>
	</select><br><br>

	<i>Distributed data processing</i>:
	<select name="DDP">
			<?php $oDDP = array(0,1,2,3,4,5);
			foreach ($oDDP as $DDP) {
				$sDDP = @$_POST['DDP'] == $DDP ? ' selected="selected"' : '';
				echo '<option value="' . $DDP . '"' . $sDDP . '>' . $DDP . '</option>';
			}?>
	</select><br><br>

	<i>Performance</i>:
	<select name="P">
			<?php $oP = array(0,1,2,3,4,5);
			foreach ($oP as $P) {
				$sP = @$_POST['P'] == $P ? ' selected="selected"' : '';
				echo '<option value="' . $P . '"' . $sP . '>' . $P . '</option>';
			}?>
	</select><br><br>
	
	<i>Heavily used configuration</i>:
	<select name="HUC">
			<?php $oHUC = array(0,1,2,3,4,5);
			foreach ($oHUC as $HUC) {
				$sHUC = @$_POST['HUC'] == $HUC ? ' selected="selected"' : '';
				echo '<option value="' . $HUC . '"' . $sHUC . '>' . $HUC . '</option>';
			}?>
	</select><br><br>

	<i>Transaction rate</i>:
	<select name="TR">
			<?php $oTR = array(0,1,2,3,4,5);
			foreach ($oTR as $TR) {
				$sTR = @$_POST['TR'] == $TR ? ' selected="selected"' : '';
				echo '<option value="' . $TR . '"' . $sTR . '>' . $TR . '</option>';
			}?>
	</select><br><br>
	
	<i>On-Line data entry</i>:
	<select name="ODE">
			<?php $oODE = array(0,1,2,3,4,5);
			foreach ($oODE as $ODE) {
				$sODE = @$_POST['ODE'] == $ODE ? ' selected="selected"' : '';
				echo '<option value="' . $ODE . '"' . $sODE . '>' . $ODE . '</option>';
			}?>
	</select><br><br>

	<i>End-user efficiency</i>:
	<select name="EUE">
			<?php $oEUE = array(0,1,2,3,4,5);
			foreach ($oEUE as $EUE) {
				$sEUE = @$_POST['EUE'] == $EUE ? ' selected="selected"' : '';
				echo '<option value="' . $EUE . '"' . $sEUE . '>' . $EUE . '</option>';
			}?>
	</select><br><br>

	<i>On-Line update</i>:
	<select name="OLU">
			<?php $oOLU = array(0,1,2,3,4,5);
			foreach ($oOLU as $OLU) {
				$sOLU = @$_POST['OLU'] == $OLU ? ' selected="selected"' : '';
				echo '<option value="' . $OLU . '"' . $sOLU . '>' . $OLU . '</option>';
			}?>
	</select><br><br>

	<i>Complex processing</i>:
	<select name="CP">
			<?php $oCP = array(0,1,2,3,4,5);
			foreach ($oCP as $CP) {
				$sCP = @$_POST['CP'] == $CP ? ' selected="selected"' : '';
				echo '<option value="' . $CP . '"' . $sCP . '>' . $CP . '</option>';
			}?>
	</select><br><br>

	<i>Reusability</i>:
	<select name="R">
			<?php $oR = array(0,1,2,3,4,5);
			foreach ($oR as $R) {
				$sR = @$_POST['R'] == $R ? ' selected="selected"' : '';
				echo '<option value="' . $R . '"' . $sR . '>' . $R . '</option>';
			}?>
	</select><br><br>
	
	<i>Installation ease</i>:
	<select name="IE">
			<?php $oIE = array(0,1,2,3,4,5);
			foreach ($oIE as $IE) {
				$sIE = @$_POST['IE'] == $IE ? ' selected="selected"' : '';
				echo '<option value="' . $IE . '"' . $sIE . '>' . $IE . '</option>';
			}?>
	</select><br><br>

	<i>Operational ease</i>:
	<select name="OE">
			<?php $oOE = array(0,1,2,3,4,5);
			foreach ($oOE as $OE) {
				$sOE = @$_POST['OE'] == $OE ? ' selected="selected"' : '';
				echo '<option value="' . $OE . '"' . $sOE . '>' . $OE . '</option>';
			}?>
	</select><br><br>

	<i>Multiple sites</i>:
	<select name="MS">
			<?php $oMS = array(0,1,2,3,4,5);
			foreach ($oMS as $MS) {
				$sMS = @$_POST['MS'] == $MS ? ' selected="selected"' : '';
				echo '<option value="' . $MS . '"' . $sMS . '>' . $MS . '</option>';
			}?>
	</select><br><br>

	<i>Facilitate change</i>:
	<select name="FC">
			<?php $oFC = array(0,1,2,3,4,5);
			foreach ($oFC as $FC) {
				$sFC = @$_POST['FC'] == $FC ? ' selected="selected"' : '';
				echo '<option value="' . $FC . '"' . $sFC . '>' . $FC . '</option>';
			}?>
	</select><br><br>
	<input type="submit" name="submit" value="Hitung"/><br><br>
	<?php
		if (isset($_POST['submit'])) {
		echo 'Nilai <i>Function Point</i>: ' . ( ($_POST['EIm']*3 + $_POST['EIs']*4 + $_POST['EIr']*6) + ($_POST['EOm']*4 + $_POST['EOs']*5 + $_POST['EOr']*7) + ($_POST['ILFm']*7 + $_POST['ILFs']*10 + $_POST['ILFr']*15) + ($_POST['EIFm']*5 + $_POST['EIFs']*7 + $_POST['EIFr']*10) + ($_POST['EInm']*3 + $_POST['EIns']*4 + $_POST['EInr']*6) ) * (0.65 + 0.01 * ($_POST['DC']+$_POST['DDP']+$_POST['P']+$_POST['HUC']+$_POST['TR']+$_POST['ODE']+$_POST['EUE']+$_POST['OLU']+$_POST['CP']+$_POST['R']+$_POST['IE']+$_POST['OE']+$_POST['MS']+$_POST['FC']));
	}?>
	</center>	
	</form>

</body>
</html>
