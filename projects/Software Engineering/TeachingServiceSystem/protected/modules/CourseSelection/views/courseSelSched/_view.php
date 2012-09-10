<div class="view">

	<b><?php echo CHtml::encode($data->getAttributeLabel('ID')); ?>:</b>
	<?php echo CHtml::link(CHtml::encode($data->ID), array('view', 'id'=>$data->ID)); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('STU_ID')); ?>:</b>
	<?php echo CHtml::encode($data->STU_ID); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('CLASS_ID')); ?>:</b>
	<?php echo CHtml::encode($data->CLASS_ID); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('REQUIRED')); ?>:</b>
	<?php echo CHtml::encode($data->REQUIRED); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('REPEATED')); ?>:</b>
	<?php echo CHtml::encode($data->REPEATED); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('ABANDONED')); ?>:</b>
	<?php echo CHtml::encode($data->ABANDONED); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('SCORE')); ?>:</b>
	<?php echo CHtml::encode($data->SCORE); ?>
	<br />

	<?php /*
	<b><?php echo CHtml::encode($data->getAttributeLabel('YEAR')); ?>:</b>
	<?php echo CHtml::encode($data->YEAR); ?>
	<br />

	*/ ?>

</div>