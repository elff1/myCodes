<div class="view">

	<b><?php echo CHtml::encode($data->getAttributeLabel('id')); ?>:</b>
	<?php echo CHtml::link(CHtml::encode($data->id), array('view', 'id'=>$data->id)); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('system_admin_id')); ?>:</b>
	<?php echo CHtml::encode($data->system_admin_id); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('personal_info_id')); ?>:</b>
	<?php echo CHtml::encode($data->personal_info_id); ?>
	<br />


</div>