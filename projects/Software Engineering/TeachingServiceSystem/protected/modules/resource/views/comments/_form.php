<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'comments-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'message'); ?>
		<?php echo $form->textArea($model,'message',array('rows'=>6, 'cols'=>50)); ?>
		<?php echo $form->error($model,'message'); ?>
	</div>

	<!-- 
	<div class="row">
		<?php echo $form->labelEx($model,'userId'); ?>
		<?php echo $form->textField($model,'userId',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'userId'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'createDate'); ?>
		<?php echo $form->textField($model,'createDate'); ?>
		<?php echo $form->error($model,'createDate'); ?>
	</div>
	 -->
	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->