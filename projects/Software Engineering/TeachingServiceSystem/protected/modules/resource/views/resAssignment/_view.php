<div class="view">

<!--	<b><?php echo CHtml::encode($data->getAttributeLabel('id')); ?>:</b>-->
<b><?php echo ResourceModule::t('resAssignment', 'Name'); ?>:</b>
	<?php echo CHtml::link($data->resource->display_name, array('view', 'id'=>$data->id)); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('teachingclass_id')); ?>:</b>
	<?php echo CHtml::encode($data->teachingclass_id); ?>
	<br />

	<!--<b><?php echo CHtml::encode($data->getAttributeLabel('resource_id')); ?>:</b>
    <?php echo CHtml::encode($data->resource_id); ?>
	<br />-->
<?php
    if ($data->dead_line < date('Y-m-d H:i:s',time())){
            echo "<span style='color:red;'>";
    }
?>
	<b><?php echo CHtml::encode($data->getAttributeLabel('dead_line')); ?>:</b>
	<?php echo CHtml::encode($data->dead_line); ?>
	<br /></span>

	<b><?php echo CHtml::encode($data->getAttributeLabel('is_published')); ?>:</b>
	<?php echo CHtml::encode($data->is_published==1? ResourceModule::t('resAssignment', 'Yes') : ResourceModule::t('resAssignment', 'No')); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('teacher_id')); ?>:</b>
    <!--<?php echo CHtml::encode($data->teacher_id); ?>-->
    <?php echo CHtml::encode($data->teacher->teacher_id); ?>
	<br />


	<b><?php echo CHtml::encode($data->getAttributeLabel('requirement')); ?>:</b>
    <?php //echo CHtml::encode($data->requirement);
        echo $data->requirement;
        // filter is done in input
    ?>
	<br />

<?php
    // show the upload homework link to student
    // show the show relates homework link to teacher
    if (Yii::app()->user->type == UserAuthentication::TYPE_STUDENT) {
        echo CHtml::link(ResourceModule::t('resAssignment', 'Upload homework'), 'index.php?r=resource/resHomework/create&assignment_id='.strval($data->id)); 
    } else {
        echo CHtml::link(ResourceModule::t('resAssignment', 'View Homeworks'), 'index.php?r=resource/resHomework/index&teachingclass_id='.strval($data->teachingclass_id).'&assignment_id='.strval($data->id));
    }
?>

</div>
