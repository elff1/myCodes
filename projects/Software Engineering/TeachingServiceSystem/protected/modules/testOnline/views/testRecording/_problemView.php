<?php 
/**
 * view for problem. If it's single choice, then we display 'a,b,c,d'
 * If it's a true-false judge, display true/false;
 */
?>
<div class="view"> 
	<b><?php echo CHtml::encode($data->getAttributeLabel('id')); ?>:</b>
	<?php echo CHtml::link(CHtml::encode($data->id), array('view', 'id'=>$data->id)); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('student_id')); ?>:</b>
	<?php echo CHtml::encode($data->student_id); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('paper_pro_id')); ?>:</b>
	<?php echo CHtml::encode($data->paper_pro_id); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('choose')); ?>:</b>
	<?php echo CHtml::encode($data->choose); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('is_commit')); ?>:</b>
	<?php echo CHtml::encode($data->is_commit); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('score')); ?>:</b>
	<?php echo CHtml::encode($data->score); ?>
	<br />


</div>