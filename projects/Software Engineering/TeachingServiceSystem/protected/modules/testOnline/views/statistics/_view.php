<div class="view">
    
	<b><?php echo CHtml::encode($data->getAttributeLabel('id')); ?>:</b>
	<?php echo CHtml::link(CHtml::encode($data->id), array('view', 'id'=>$data->id)); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('done')); ?>:</b>
	<?php echo CHtml::encode($data->done); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('a')); ?>:</b>
	<?php echo CHtml::encode($data->a); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('b')); ?>:</b>
	<?php echo CHtml::encode($data->b); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('c')); ?>:</b>
	<?php echo CHtml::encode($data->c); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('d')); ?>:</b>
	<?php echo CHtml::encode($data->d); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('pro_id')); ?>:</b>
	<?php echo CHtml::encode($data->pro_id); ?>
	<br />


</div>