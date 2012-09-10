<div class="view">
	<?php echo CHtml::encode('Course Number'); ?>:
	<?php echo CHtml::link(CHtml::encode($data->course_id),array('default/updateSelectedCourse','course_id'=>$data->id)); ?>
	<br />

	<?php echo CHtml::encode('Course Name'); ?>:
	<?php echo CHtml::encode($data->name) ;?>
	<br />
</div>
			