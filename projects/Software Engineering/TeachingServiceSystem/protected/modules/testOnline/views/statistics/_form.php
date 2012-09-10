<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'statistics-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'done'); ?>
		<?php echo $form->textField($model,'done'); ?>
		<?php echo $form->error($model,'done'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'a'); ?>
		<?php echo $form->textField($model,'a'); ?>
		<?php echo $form->error($model,'a'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'b'); ?>
		<?php echo $form->textField($model,'b'); ?>
		<?php echo $form->error($model,'b'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'c'); ?>
		<?php echo $form->textField($model,'c'); ?>
		<?php echo $form->error($model,'c'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'d'); ?>
		<?php echo $form->textField($model,'d'); ?>
		<?php echo $form->error($model,'d'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'pro_id'); ?>
		<?php echo $form->textField($model,'pro_id',array('size'=>20,'maxlength'=>20)); ?>
		<?php echo $form->error($model,'pro_id'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->