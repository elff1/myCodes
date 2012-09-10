<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'paper-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'paper_id'); ?>
		<?php echo $form->textField($model,'paper_id',array('size'=>10,'maxlength'=>10)); ?>
		<?php echo $form->error($model,'paper_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'pro_id'); ?>
		<?php echo $form->textField($model,'pro_id',array('size'=>20,'maxlength'=>20)); ?>
		<?php echo $form->error($model,'pro_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'pro_score'); ?>
		<?php echo $form->textField($model,'pro_score'); ?>
		<?php echo $form->error($model,'pro_score'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->