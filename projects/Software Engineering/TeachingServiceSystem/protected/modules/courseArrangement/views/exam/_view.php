<div class="view">

	<b><?php echo CHtml::encode($data->getAttributeLabel('id')); ?>:</b>
	<?php echo CHtml::link(CHtml::encode($data->id), array('view', 'id'=>$data->id)); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('class_id')); ?>:</b>
	<?php echo CHtml::encode($data->class_id); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('classroom_id')); ?>:</b>
	<?php echo CHtml::encode($data->classroom_id); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('teacher1_id')); ?>:</b>
	<?php echo CHtml::encode($data->teacher1_id); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('teacher2_id')); ?>:</b>
	<?php echo CHtml::encode($data->teacher2_id); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('exam_time')); ?>:</b>
	<?php echo CHtml::encode($data->exam_time); ?>
	<br />


</div>