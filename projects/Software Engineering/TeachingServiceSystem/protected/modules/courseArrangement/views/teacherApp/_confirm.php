<div class="view">

	<b><?php echo CHtml::encode($data->getAttributeLabel('id')); ?>:</b>
	<?php echo CHtml::link(CHtml::encode($data->id), array('view', 'id'=>$data->id)); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('preferPlace')); ?>:</b>
	<?php echo CHtml::encode($data->preferPlace); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('preferTime')); ?>:</b>
	<?php echo CHtml::encode($data->preferTime); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('courseID')); ?>:</b>
	<?php echo CHtml::encode($data->courseID); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('name')); ?>:</b>
	<?php echo CHtml::encode($data->name); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('teacherID')); ?>:</b>
	<?php echo CHtml::encode($data->teacherID); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('appTime')); ?>:</b>
	<?php echo CHtml::encode($data->appTime); ?>
	<br />
	<br />
	<b><?php echo CHtml::encode($data->getAttributeLabel('pass')); ?>:</b>
	<?php 
	$id =  CHtml::encode($data->id); 
	echo "<div id='" .$id. "'>";
	
	$pass = CHtml::encode($data->pass);
	if($pass=="waiting")
	{
		echo "<font color=\"blue\">";
	}
	else if($pass=="yes")
	{
		echo "<font color=\"green\">";
	}
	else
	{
		echo "<font color=\"red\">";
	}
	echo CHtml::encode($data->pass); 
	echo "</font>";
	echo "</div>";
	?>
	<br />
	
	
	
	<?php
	$id =  CHtml::encode($data->id); 
	
	//echo "<a href=\"javascript:pass('". $id . "','yes');\">同意 </a><br />";
	//echo "<a href=\"javascript:pass('". $id . "','no');\">不同意 </a>";
	echo "<button type=\"button\" onclick=\"pass('". $id . "','yes');\">同意</button>&nbsp&nbsp&nbsp";
	echo "<button type=\"button\" onclick=\"pass('". $id . "','no');\">不同意</button>";
	
	?>
	<br />

</div>