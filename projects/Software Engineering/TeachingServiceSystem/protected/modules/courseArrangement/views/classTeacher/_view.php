<div class="view">

	<b><?php echo CHtml::encode($data->getAttributeLabel('id')); ?>:</b>
	<?php echo CHtml::link(CHtml::encode($data->id), array('view', 'id'=>$data->id)); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('teacherid')); ?>:</b>
	<?php echo CHtml::encode($data->teacherid); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('classid')); ?>:</b>
	<?php echo CHtml::encode($data->classid); ?>
	<br />


</div>