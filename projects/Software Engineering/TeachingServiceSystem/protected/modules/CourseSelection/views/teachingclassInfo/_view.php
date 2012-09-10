<div class="view">

	<b><?php echo CHtml::encode($data->getAttributeLabel('class_id')); ?>:</b>
	<?php echo CHtml::link(CHtml::encode($data->class_id), array('view', 'id'=>$data->class_id)); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('course_num')); ?>:</b>
	<?php echo CHtml::encode($data->course_num); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('max')); ?>:</b>
	<?php echo CHtml::encode($data->max); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('term')); ?>:</b>
	<?php echo CHtml::encode($data->term); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('campus')); ?>:</b>
	<?php echo CHtml::encode($data->campus); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('dependence')); ?>:</b>
	<?php echo CHtml::encode($data->dependence); ?>
	<br />


</div>