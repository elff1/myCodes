<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'student-achievement-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'id'); ?>
		<?php echo $form->textField($model,'id',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'gpa_major'); ?>
		<?php echo $form->textField($model,'gpa_major'); ?>
		<?php echo $form->error($model,'gpa_major'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'gpa_total'); ?>
		<?php echo $form->textField($model,'gpa_total'); ?>
		<?php echo $form->error($model,'gpa_total'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'credit_total'); ?>
		<?php echo $form->textField($model,'credit_total'); ?>
		<?php echo $form->error($model,'credit_total'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'credit_achieve'); ?>
		<?php echo $form->textField($model,'credit_achieve'); ?>
		<?php echo $form->error($model,'credit_achieve'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'credit_major_total'); ?>
		<?php echo $form->textField($model,'credit_major_total'); ?>
		<?php echo $form->error($model,'credit_major_total'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'credit_major_achieve'); ?>
		<?php echo $form->textField($model,'credit_major_achieve'); ?>
		<?php echo $form->error($model,'credit_major_achieve'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->