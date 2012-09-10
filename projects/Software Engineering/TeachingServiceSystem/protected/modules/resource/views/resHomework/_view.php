<div class="view">

<b><?php echo ResourceModule::t('resHomework', 'Name'); ?></b>
<?php echo CHtml::link(CHtml::encode($data->student->student_id), array('view', 'id'=>$data->id));?>
<!--
	<b><?php echo CHtml::encode($data->getAttributeLabel('id')); ?>:</b>
    <?php echo CHtml::link(CHtml::encode($data->id), array('view', 'id'=>$data->id)); ?>
-->
    <br />

<!--	<b><?php echo CHtml::encode($data->getAttributeLabel('student_id')); ?>:</b>
	<?php echo CHtml::encode($data->student_id); ?>
    <br />
     -->   

	<b><?php echo CHtml::encode($data->getAttributeLabel('score')); ?>:</b>
<!--
	<?php echo CHtml::encode($data->score); ?>
    <br />
-->
    <?php 
        if ($data->score==-1) {
            echo 'Not graded';
        } else {
            echo CHtml::encode($data->score);
        }
    ?><br />

    <b><?php echo CHtml::encode($data->getAttributeLabel('assignment_id')); ?>:</b>
<?php
        $res = ResResource::model()->findbyPk($data->assignment->resource_id);
?>
	<?php echo CHtml::encode($res->display_name); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('teachingclass_id')); ?>:</b>
	<?php echo CHtml::encode($data->teachingclass_id); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('comments')); ?>:</b>
    <?php //echo CHtml::encode($data->comments);
        echo $data->comments; ?>
	<br />
<!--
	<b><?php echo CHtml::encode($data->getAttributeLabel('resource_id')); ?>:</b>
    <?php echo CHtml::encode($data->resource_id); ?>
-->
<?php $res_data = $data->resource; ?>
<b><?php echo ResourceModule::t('resHomework', 'Description'); ?></b>
    <?php echo $res_data->description; ?><br />
    <b><?php echo ResourceModule::t('resHomework', 'Download'); ?></b> 
    <?php echo CHtml::link(ResourceModule::t('resHomework', 'Click Here'), '/protected/uploads/res/'.strval($res_data->uploader_id).'+'.$res_data->path); ?>
	<br />
    
<?php
    if ($data->submit_time > ResAssignment::model()->
        findbyPk($data->assignment_id)->dead_line){
            echo "<span style='color:red;'>";
    }
?>
    <b><?php echo CHtml::encode($data->getAttributeLabel('submit_time')); ?>:</b>

	<?php echo CHtml::encode($data->submit_time); ?>
	<br /></span>
    


</div>
