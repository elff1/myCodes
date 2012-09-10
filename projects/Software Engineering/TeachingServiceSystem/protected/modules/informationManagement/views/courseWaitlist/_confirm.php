<div class="view">

	<b><?php echo CHtml::encode($data->getAttributeLabel('id')); ?>:</b>
	<?php echo CHtml::link(CHtml::encode($data->id), array('view', 'id'=>$data->id)); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('name')); ?>:</b>
	<?php echo CHtml::encode($data->name); ?>
	<br />
	
	<b><?php echo CHtml::encode($data->getAttributeLabel('credit')); ?>:</b>
	<?php echo CHtml::encode($data->credit); ?>
	<br />
	
	<b><?php echo CHtml::encode($data->getAttributeLabel('class')); ?>:</b>
	<?php echo CHtml::encode($data->class); ?>
	<br />
	
	<b><?php echo CHtml::encode($data->getAttributeLabel('prerequsite_required')); ?>:</b>
	<?php echo CHtml::encode($data->prerequsite_required); ?>
	<br />
	
	<b><?php echo CHtml::encode($data->getAttributeLabel('introduction')); ?>:</b>
	<?php echo CHtml::encode($data->introduction); ?>
	<br />
	
	<b><?php echo CHtml::encode($data->getAttributeLabel('syllabus')); ?>:</b>
	<?php echo CHtml::encode($data->syllabus); ?>
	<br />
	
	<b><?php echo CHtml::encode($data->getAttributeLabel('statement')); ?>:</b>
	<?php echo CHtml::encode($data->statement); ?>
	<br />
	
	<b><?php echo CHtml::encode($data->getAttributeLabel('department_id')); ?>:</b>
	<?php echo CHtml::encode($data->department==null?$null:$data->department->name); ?>
	<br />
	
	<b><?php echo CHtml::encode($data->getAttributeLabel('priority')); ?>:</b>
	<?php echo CHtml::encode($data->priority); ?>
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
	echo "<button type=\"button\" onclick=\"pass('". $id . "','yes');\">同意</button>&nbsp&nbsp&nbsp";
	echo "<button type=\"button\" onclick=\"pass('". $id . "','no');\">不同意</button>";
	?>
	<br />

</div>