<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'course-sel-sched-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'STU_ID'); ?>
		<?php echo $form->textField($model,'STU_ID',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'STU_ID'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'CLASS_ID'); ?>
		<?php echo $form->textField($model,'CLASS_ID'); ?>
		<?php echo $form->error($model,'CLASS_ID'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'REQUIRED'); ?>
		<?php echo $form->textField($model,'REQUIRED',array('size'=>1,'maxlength'=>1)); ?>
		<?php echo $form->error($model,'REQUIRED'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'REPEATED'); ?>
		<?php echo $form->textField($model,'REPEATED',array('size'=>1,'maxlength'=>1)); ?>
		<?php echo $form->error($model,'REPEATED'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'ABANDONED'); ?>
		<?php echo $form->textField($model,'ABANDONED',array('size'=>1,'maxlength'=>1)); ?>
		<?php echo $form->error($model,'ABANDONED'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'SCORE'); ?>
		<?php echo $form->textField($model,'SCORE'); ?>
		<?php echo $form->error($model,'SCORE'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'YEAR'); ?>
		<?php echo $form->textField($model,'YEAR'); ?>
		<?php echo $form->error($model,'YEAR'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->