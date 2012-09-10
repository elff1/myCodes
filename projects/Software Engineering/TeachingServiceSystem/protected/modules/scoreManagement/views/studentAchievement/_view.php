<div class="view">

	<b><?php echo CHtml::encode($data->getAttributeLabel('id')); ?>:</b>
	<?php echo CHtml::link(CHtml::encode($data->id), array('view', 'id'=>$data->id)); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('gpa_major')); ?>:</b>
	<?php echo CHtml::encode($data->gpa_major); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('gpa_total')); ?>:</b>
	<?php echo CHtml::encode($data->gpa_total); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('credit_total')); ?>:</b>
	<?php echo CHtml::encode($data->credit_total); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('credit_achieve')); ?>:</b>
	<?php echo CHtml::encode($data->credit_achieve); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('credit_major_total')); ?>:</b>
	<?php echo CHtml::encode($data->credit_major_total); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('credit_major_achieve')); ?>:</b>
	<?php echo CHtml::encode($data->credit_major_achieve); ?>
	<br />


</div>