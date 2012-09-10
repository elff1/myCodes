<div class="view" id = <?php echo "\"".CHtml::encode($data->id)."\""?>> 

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
	
	<b><?php echo CHtml::encode($data->getAttributeLabel('pass')); ?>:</b>
	<?php
		$id = CHtml::encode($data->id);
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

		if($pass=="waiting")
		{
			echo"";
			echo "<button type=\"button\" onclick=\"appDelete('". $id . "');\">撤销</button>&nbsp&nbsp&nbsp";
			echo "<button type=\"button\" onclick=\"appUpdate('". $id . "');\">修改</button>";
			//echo CHtml::link("撤销", array('delete', 'id'=>$data->id));
		}


	?>
	<br />

</div>