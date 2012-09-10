<div class="view">

	<!-- 
	<b><?php echo CHtml::encode($data->getAttributeLabel('id')); ?>:</b>
	<?php echo CHtml::link(CHtml::encode($data->id), array('view', 'id'=>$data->id)); ?>
	<br />
 	-->
 	
 	<!-- 
	<b><?php echo CHtml::encode($data->getAttributeLabel('path')); ?>:</b>
	<?php echo CHtml::encode($data->path); ?>
	<br />
 	-->
 	
	<b><?php echo CHtml::encode($data->getAttributeLabel('display_name')); ?>:</b>
	<?php echo CHtml::link(CHtml::encode($data->display_name), array('view', 'id'=>$data->id)); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('uploader_id')); ?>:</b>
	<?php echo CHtml::encode($data->uploader_id); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('download_count')); ?>:</b>
	<?php echo CHtml::encode($data->download_count); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('resource_type')); ?>:</b>
	<?php echo CHtml::encode($data->resource_type); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('description')); ?>:</b>
	<?php echo CHtml::encode($data->description); ?>
	<br />

	<?php /*
	<b><?php echo CHtml::encode($data->getAttributeLabel('upload_time')); ?>:</b>
	<?php echo CHtml::encode($data->upload_time); ?>
	<br />

	*/ ?>

</div>