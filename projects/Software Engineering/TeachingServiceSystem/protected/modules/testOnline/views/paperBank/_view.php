<div class="view">
	<!-- the id view row -->
	<b><?php echo CHtml::encode($data->getAttributeLabel('id')); ?>:</b>
	<?php echo CHtml::link(CHtml::encode($data->id), array('default/updateSelectedPaper', 'paper_id'=>$data->id)); ?>
	<br />

	<!-- the is_publish view row -->
	<b><?php echo CHtml::encode($data->getAttributeLabel('is_publish')); ?>:</b>
	<?php echo CHtml::encode($data->getIsPublish()); ?>
	<br />

	<!-- the timelimit view row -->
	<b><?php echo CHtml::encode($data->getAttributeLabel('timelimit')); ?>:</b>
	<?php echo CHtml::encode($data->timelimit); ?>
	<br />

	<!-- the average score -->
	<b><?php echo CHtml::encode('Average Score'); ?>:</b>
	<?php echo CHtml::encode(statistics::getAverageGrade($data->id));// + CHtml::encode('/100'); ?>
	<br />

</div>