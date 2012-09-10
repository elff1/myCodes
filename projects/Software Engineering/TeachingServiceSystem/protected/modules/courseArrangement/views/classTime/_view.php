<div class="view">

	<b><?php echo CHtml::encode($data->getAttributeLabel('id')); ?>:</b>
	<?php echo CHtml::link(CHtml::encode($data->id), array('view', 'id'=>$data->id)); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('class_id')); ?>:</b>
	<?php 
	echo CHtml::encode($data->class_id); 
	$class_id = CHtml::encode($data->class_id);
	$class_teachers = ClassTeacher::model()->findAllBySql("select *from class_teacher where classid=".$class_id,array());
	
	echo "<br /><b>".Yii::t('courseArrangement','teacherid').":</b>";
	//echo "select *from class_teacher where classid=".$class_id."<br />";
	foreach($class_teachers as $class_teacher)
	{
		$teacher_id = $class_teacher->teacherid;
		
		echo $teacher_id;
		//$teacher = ClassroomBasicInfo::model()->findAllByPK($classroom_id);
	}
	?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('classroom_id')); ?>:</b>
	<?php 
	
	$classroom_id =  CHtml::encode($data->classroom_id); 
	$classroom = ClassroomBasicInfo::model()->findAllByPK($classroom_id);
	echo $classroom[0]->room_number;
	?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('time')); ?>:</b>
	<?php echo CHtml::encode($data->time); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('isSingle')); ?>:</b>
	<?php echo CHtml::encode($data->isSingle); ?>
	<br />


</div>