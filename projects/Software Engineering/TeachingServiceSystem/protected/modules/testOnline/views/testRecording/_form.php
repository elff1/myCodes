<div class="form">

<?php

$form = $this->beginWidget ( 'CActiveForm', array (
		'id' => 'test-recording-form',
		'enableAjaxValidation' => false 
) );
$problem = $model->paperPro->problems;
?>

	<p class="note">
		Fields with <span class="required">*</span> are required.
	</p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo CHtml::encode($problem->getAttributeLabel('question')); ?>:</b>
		<?php echo CHtml::encode($problem->question); ?>
	</div>
	<div class="row">
		<?php echo $form->hiddenField($model,'paper_pro_id')?>
	</div>
	<div class="row">
	<?php echo $form->labelEx($model,'Select Your answer'); ?>
	<?php if($problem->type == QuestionBank::$CHOICE_TYPE) :?>
		<?php echo $form->checkBoxList($model,'choose',array('A'=>$problem->selection_a,'B'=>$problem->selection_b,'C'=>$problem->selection_c,'D'=>$problem->selection_d)); ?>
	<?php else:  ?>
		<?php echo $form->checkBoxList($model,'choose',array('T'=>('true'),'F'=>('false'))); ?>
	<?php endif; ?>
	<?php echo $form->error($model,'choose'); ?>
	</div>
	
	<div class="row buttons">
		<?php echo CHtml::submitButton('Submit'); ?>
	</div>

<?php $this->endWidget(); ?>

</div>
<!-- form -->